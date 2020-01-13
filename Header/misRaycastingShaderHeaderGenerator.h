#pragma  once;

#include <iostream>
#include <string>
#include <string.h>


#include "IShaderHeaderGenerator.h"
#include "misCroppingDirectionInVR.h"
#include "volumeraycaster.h"
#include "misImageContainedDataType.h"
#include "TransferFuncs3D.h"

namespace voreen
{

	class misRaycastingShaderHeaderGenerator: public IShaderHeaderGenerator
	{

	public:


		misRaycastingShaderHeaderGenerator::misRaycastingShaderHeaderGenerator(
			const std::vector<ImageContainedTransferFuncs3D> &, const StringOptionProperty& );

		virtual void ComposeHeader() override;

		void AppendSamplerTypesDefinitions();

		void AppendTransferFunctionsDefinitions();

		void AppendActiveVolumesDefinitions();

		void AppendCompositingModeDefinitions();

		virtual std::string GetHeader() const override;

		virtual void setVoreenGeneratedHeader(std::string) override;
		virtual void setCroppingDirectionInVR(misCroppingDirectionInVR) override;
		virtual void setNumOfVolumes(int) override;

	private:



		const std::vector<ImageContainedTransferFuncs3D> &m_GroupTransferFunctions;
		const StringOptionProperty &m_compositingMode_;
		misCroppingDirectionInVR m_cropDirection;
		std::string m_VorrenGeneratedHeader;
		int m_numOfVolumes;

		std::stringstream m_GeneratedHeader;
		std::string ConvertTransferFunctionIndexToString( int volumeIndex , int TfIndex );
		std::string ConvertVolumeIndexToString( int volumeIndex );
		std::string ConvertVolumeParameterToString( int volumeIndex );
		void AppendCroppingDirective();



	};
}