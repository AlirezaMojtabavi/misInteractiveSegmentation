#include "stdafx.h"
#include "misOpenGLContextSharing.h"
#include "IWindows.h"

void misOpenGLContextSharing::ShareContexts(std::vector<std::shared_ptr<Iwindows>> source,
	std::vector<std::shared_ptr<Iwindows>> dest)
{
	for (auto sourceWindow : source)
	{
		for (auto destWindow : dest)
		{
			const auto sourceWindowsContextId = sourceWindow->GetContextId();
			const auto destWindowsContextId = destWindow->GetContextId();
			if (sourceWindowsContextId != destWindowsContextId)
			{
				const auto sharingResult = wglShareLists(sourceWindowsContextId,destWindowsContextId);
				//_ASSERT(sharingResult == TRUE);
			}
		}
	}
}
