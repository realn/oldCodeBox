#include "../Internal/BaseShader.h"
#include "../Internal/BaseTexture.h"
#include <CBStringEx.h>

namespace CB{
	IOGLBaseShader::IOGLBaseShader(CRefPtr<COGLDevice> pDevice, const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, CGenum uSourceType, CGprofile uProfile, const CString& strSource, const CString& strEntryPoint) :
		m_uVersion(uVersion),
		m_uType(uType),
		m_uProgram(0),
		m_bBinded(false),
		Manage::IManagedObject<COGLDevice, IOGLBaseShader>(pDevice)
	{
		if(!cgIsProfileSupported(uProfile)){
			throw Exception::CInvalidArgumentException(L"uProfile", String::FromANSI(reinterpret_cast<const int8*>(cgGetProfileString(uProfile))),
				L"Unsupported shader profile.", CR_INFO());
		}

		auto szSource = String::ToANSI(strSource);
		auto szEntryPoint = String::ToANSI(strEntryPoint);

		this->m_uProgram = cgCreateProgram(this->GetParent()->GetCGContext(), uSourceType, reinterpret_cast<const char*>(szSource.GetPointer()), uProfile, reinterpret_cast<const char*>(szEntryPoint.GetPointer()), 0);
		if(!cgIsProgram(this->m_uProgram)){
			CR_THROW(L"Failed to create shader program.");
		}

		cgCompileProgram(this->m_uProgram);
		if(!cgIsProgramCompiled(this->m_uProgram)){
			CR_THROW(L"Failed to compile program.");
		}

		cgGLLoadProgram(this->m_uProgram);
	}

	IOGLBaseShader::~IOGLBaseShader(){
		this->UnbindParameters();
		this->UnbindSamplers();
		if(this->m_bBinded){
			this->Unbind();
		}
		if(this->m_uProgram != 0 && cgIsProgram(this->m_uProgram)){
			cgDestroyProgram(this->m_uProgram);
			this->m_uProgram = 0;
		}
	}

	CGprogram	IOGLBaseShader::GetProgram() const{
		return this->m_uProgram;
	}

	CGprofile	IOGLBaseShader::GetProfile() const{
		return cgGetProgramProfile(this->m_uProgram);
	}

	CGparameter	IOGLBaseShader::GetParameter(const CString& strName) const{
		auto szName = String::ToANSI(strName);

		auto uParam = cgGetNamedParameter(this->m_uProgram, reinterpret_cast<const char*>(szName.GetPointer()));
		if(uParam == 0 || !cgIsParameter(uParam)){
			CR_THROW(L"Failed to find parameter: " + strName);
		}

		return uParam;
	}

	void	IOGLBaseShader::RemoveSampler(CPtr<IOGLBaseTexture> pTexture){
		uint32 uIndex = 0;
		while(Collection::TryFind(this->m_pSamplerTextures, pTexture, uIndex)){
			cgGLSetTextureParameter(this->m_uSamplerParams[uIndex], 0);
			this->m_uSamplerParams.Remove(uIndex);
			this->m_pSamplerTextures.Remove(uIndex);
		}
	}

	void	IOGLBaseShader::Bind(){
		cgGLEnableProfile(this->GetProfile());
		cgGLBindProgram(this->m_uProgram);
		this->m_bBinded = true;
	}

	void	IOGLBaseShader::BindParameter(const CString& strParam, GLenum uType, const uint32 uNumber, const uint32 uStride, const uint32 uOffset){
		auto uParam = this->GetParameter(strParam);

		cgGLEnableClientState(uParam);
		cgGLSetParameterPointer(uParam, uNumber, uType, uStride, reinterpret_cast<const GLvoid*>(uOffset));
		this->m_uVaryingParams.Add(uParam);
	}

	void	IOGLBaseShader::BindSamplers(){
		for(uint32 i = 0; i < this->m_uSamplerParams.GetLength(); i++){
			cgGLEnableTextureParameter(this->m_uSamplerParams[i]);
		}
	}

	void	IOGLBaseShader::Unbind(){
		cgGLUnbindProgram(this->GetProfile());
		cgGLDisableProfile(this->GetProfile());
		this->m_bBinded = false;
	}

	void	IOGLBaseShader::UnbindParameter(const CString& strParam){
		auto uParam = this->GetParameter(strParam);

		cgGLDisableClientState(uParam);
		uint32 uIndex = 0;
		if(Collection::TryFind(this->m_uVaryingParams, uParam, uIndex)){
			this->m_uVaryingParams.Remove(uIndex);
		}
	}

	void	IOGLBaseShader::UnbindParameters(){
		for(uint32 uIndex = 0; uIndex < this->m_uVaryingParams.GetLength(); uIndex++){
			cgGLDisableClientState(this->m_uVaryingParams[uIndex]);
		}
		this->m_uVaryingParams.Clear();
	}

	void	IOGLBaseShader::UnbindSamplers(){
		for(uint32 i = 0; i < this->m_uSamplerParams.GetLength(); i++){
			cgGLDisableTextureParameter(this->m_uSamplerParams[i]);
		}
	}

	const uint32	IOGLBaseShader::GetApiId() const{
		return g_uApiID;
	}

	const Graphic::ShaderVersion	IOGLBaseShader::GetVersion() const{
		return this->m_uVersion;
	}

	const Graphic::ShaderType	IOGLBaseShader::GetType() const{
		return this->m_uType;
	}

	CRefPtr<Graphic::IDevice>	IOGLBaseShader::GetDevice() const{
		return this->GetParent().Cast<Graphic::IDevice>();
	}

	void	IOGLBaseShader::SetUniform(const CString& strName, const float fValue){
		cgGLSetParameter1f(this->GetParameter(strName), fValue);
	}

	void	IOGLBaseShader::SetUniform(const CString& strName, const Math::CVector2D& vValue){
		cgGLSetParameter2f(this->GetParameter(strName), vValue.X, vValue.Y);
	}

	void	IOGLBaseShader::SetUniform(const CString& strName, const Math::CVector3D& vValue){
		cgGLSetParameter3f(this->GetParameter(strName), vValue.X, vValue.Y, vValue.Z);
	}

	void	IOGLBaseShader::SetUniform(const CString& strName, const Math::CVector4D& vValue){
		cgGLSetParameter4f(this->GetParameter(strName), vValue.X, vValue.Y, vValue.Z, vValue.W);
	}

	void	IOGLBaseShader::SetUniform(const CString& strName, const Math::CMatrix& mValue){
		auto uParam = this->GetParameter(strName);

		cgGLSetMatrixParameterfr(uParam, mValue[0].GetPointer());
	}

	void	IOGLBaseShader::SetSampler(const CString& strName, CRefPtr<Graphic::IBaseTexture> pTexture){
		CR_APICHECK(this, pTexture);

		auto pGLTexture = pTexture.Cast<IOGLBaseTexture>();
		auto uParam = this->GetParameter(strName);

		this->FreeSampler(strName);

		cgGLSetTextureParameter(uParam, pGLTexture->GetTextureID());
		if(this->m_bBinded){
			cgGLEnableTextureParameter(uParam);
		}

		this->m_uSamplerParams.Add(uParam);
		this->m_pSamplerTextures.Add(pGLTexture);
	}

	void	IOGLBaseShader::FreeSampler(const CString& strName){
		auto uParam = this->GetParameter(strName);

		if(this->m_bBinded){
			cgGLDisableTextureParameter(uParam);
		}
		
		uint32 uIndex = 0;
		if(Collection::TryFind(this->m_uSamplerParams, uParam, uIndex)){
			cgGLSetTextureParameter(uParam, 0);
			this->m_uSamplerParams.Remove(uIndex);
			this->m_pSamplerTextures.Remove(uIndex);
		}
	}

	CRefPtr<Graphic::IBaseTexture>	IOGLBaseShader::GetSampler(const CString& strName) const{
		auto uParam = this->GetParameter(strName);

		uint32 uIndex = 0;
		if(Collection::TryFind(this->m_uSamplerParams, uParam, uIndex)){
			return this->m_pSamplerTextures[uIndex].GetCast<Graphic::IBaseTexture>();
		}

		throw Exception::CInvalidArgumentException(L"strName", strName,
			L"Parameter doesn't have an set texture.", CR_INFO());
	}
}