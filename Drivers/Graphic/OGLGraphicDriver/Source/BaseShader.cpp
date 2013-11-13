#include "../Internal/BaseShader.h"
#include <CBStringEx.h>

namespace CB{
	IOGLBaseShader::IOGLBaseShader(CRefPtr<COGLDevice> pDevice, const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, CGenum uSourceType, CGprofile uProfile, const CString& strSource, const CString& strEntryPoint) :
		m_uVersion(uVersion),
		m_uType(uType),
		m_uProgram(0),
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

	CGparameter	IOGLBaseShader::GetParameter(const CString& strName){
		auto szName = String::ToANSI(strName);

		auto uParam = cgGetNamedParameter(this->m_uProgram, reinterpret_cast<const char*>(szName.GetPointer()));
		if(uParam == 0 || !cgIsParameter(uParam)){
			CR_THROW(L"Failed to find parameter: " + strName);
		}

		return uParam;
	}

	void	IOGLBaseShader::Bind(){
		cgGLEnableProfile(this->GetProfile());
		cgGLBindProgram(this->m_uProgram);
	}

	void	IOGLBaseShader::BindParameter(const CString& strParam, GLenum uType, const uint32 uNumber, const uint32 uStride, const uint32 uOffset){
		auto uParam = this->GetParameter(strParam);

		cgGLEnableClientState(uParam);
		cgGLSetParameterPointer(uParam, uNumber, uType, uStride, reinterpret_cast<const GLvoid*>(uOffset));
	}

	void	IOGLBaseShader::Unbind(){
		cgGLUnbindProgram(this->GetProfile());
		cgGLDisableProfile(this->GetProfile());
	}

	void	IOGLBaseShader::UnbindParameter(const CString& strParam){
		auto uParam = this->GetParameter(strParam);

		cgGLDisableClientState(uParam);
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

		//cgGLSetTextureParameter(this->GetParameter(strName), 
		CR_THROWNOTIMPLEMENTED();
	}

	void	IOGLBaseShader::FreeSampler(const CString& strName){
		auto uParameter = this->GetParameter(strName);

		CR_THROWNOTIMPLEMENTED();
	}
}