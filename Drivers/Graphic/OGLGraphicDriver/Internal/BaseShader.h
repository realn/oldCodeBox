#pragma once

#include "Device.h"

namespace CB{
	class IOGLBaseShader :
		public Graphic::IShader,
		public Manage::IManagedObject<COGLDevice, IOGLBaseShader>
	{
	protected:
		const Graphic::ShaderType		m_uType;
		const Graphic::ShaderVersion	m_uVersion;
		CGprogram	m_uProgram;

		IOGLBaseShader(CRefPtr<COGLDevice> pDevice, const Graphic::ShaderType uType, const Graphic::ShaderVersion uVersion, CGenum uSourceType, CGprofile uProfile, const CString& strSource, const CString& strEntryPoint);
	public:
		~IOGLBaseShader();

		CGprogram	GetProgram() const;
		CGprofile	GetProfile() const;
		CGparameter	GetParameter(const CString& strName);

		void	Bind();
		void	BindParameter(const CString& strParam, GLenum uType, const uint32 uNumber, const uint32 uStride, const uint32 uOffset);

		void	Unbind();
		void	UnbindParameter(const CString& strParam);

		//	INTERFACE IMPLEMENTATION	============================================

		const uint32	GetApiId() const override;

		const Graphic::ShaderVersion	GetVersion() const override;
		const Graphic::ShaderType		GetType() const override;

		CRefPtr<Graphic::IDevice>	GetDevice() const override;

		void	SetUniform(const CString& strName, const float fValue) override;
		void	SetUniform(const CString& strName, const Math::CVector2D& vValue) override;
		void	SetUniform(const CString& strName, const Math::CVector3D& vValue) override;
		void	SetUniform(const CString& strName, const Math::CVector4D& vValue) override;
		void	SetUniform(const CString& strName, const Math::CMatrix& mValue) override;
		
		void	SetSampler(const CString& strName, CRefPtr<Graphic::IBaseTexture> pTexture) override;
		void	FreeSampler(const CString& strName) override;

		//	END OF IMPLEMENTATION	================================================
	};
}