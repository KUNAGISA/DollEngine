// generated from gentext.pl Messages.xlsx
#ifndef __TJS_ERROR_INC_H__
#define __TJS_ERROR_INC_H__
#ifndef TJS_MSG_DECL
	#define TJS_MSG_DECL(name, msg) extern tTJSMessageHolder name;
	#define TJS_MSG_DECL_NULL(name) extern tTJSMessageHolder name;
#endif
extern void TVPLoadMessage();
TJS_MSG_DECL_NULL(TJSInternalError)
TJS_MSG_DECL_NULL(TJSWarning)
TJS_MSG_DECL_NULL(TJSWarnEvalOperator)
TJS_MSG_DECL_NULL(TJSNarrowToWideConversionError)
TJS_MSG_DECL_NULL(TJSVariantConvertError)
TJS_MSG_DECL_NULL(TJSVariantConvertErrorToObject)
TJS_MSG_DECL_NULL(TJSIDExpected)
TJS_MSG_DECL_NULL(TJSSubstitutionInBooleanContext)
TJS_MSG_DECL_NULL(TJSCannotModifyLHS)
TJS_MSG_DECL_NULL(TJSInsufficientMem)
TJS_MSG_DECL_NULL(TJSCannotGetResult)
TJS_MSG_DECL_NULL(TJSNullAccess)
TJS_MSG_DECL_NULL(TJSMemberNotFound)
TJS_MSG_DECL_NULL(TJSMemberNotFoundNoNameGiven)
TJS_MSG_DECL_NULL(TJSNotImplemented)
TJS_MSG_DECL_NULL(TJSInvalidParam)
TJS_MSG_DECL_NULL(TJSBadParamCount)
TJS_MSG_DECL_NULL(TJSInvalidType)
TJS_MSG_DECL_NULL(TJSSpecifyDicOrArray)
TJS_MSG_DECL_NULL(TJSSpecifyArray)
TJS_MSG_DECL_NULL(TJSStringDeallocError)
TJS_MSG_DECL_NULL(TJSStringAllocError)
TJS_MSG_DECL_NULL(TJSMisplacedBreakContinue)
TJS_MSG_DECL_NULL(TJSMisplacedCase)
TJS_MSG_DECL_NULL(TJSMisplacedReturn)
TJS_MSG_DECL_NULL(TJSStringParseError)
TJS_MSG_DECL_NULL(TJSNumberError)
TJS_MSG_DECL_NULL(TJSUnclosedComment)
TJS_MSG_DECL_NULL(TJSInvalidChar)
TJS_MSG_DECL_NULL(TJSExpected)
TJS_MSG_DECL_NULL(TJSSyntaxError)
TJS_MSG_DECL_NULL(TJSPPError)
TJS_MSG_DECL_NULL(TJSCannotGetSuper)
TJS_MSG_DECL_NULL(TJSInvalidOpecode)
TJS_MSG_DECL_NULL(TJSRangeError)
TJS_MSG_DECL_NULL(TJSAccessDenyed)
TJS_MSG_DECL_NULL(TJSNativeClassCrash)
TJS_MSG_DECL_NULL(TJSInvalidObject)
TJS_MSG_DECL_NULL(TJSCannotOmit)
TJS_MSG_DECL_NULL(TJSCannotParseDate)
TJS_MSG_DECL_NULL(TJSInvalidValueForTimestamp)
TJS_MSG_DECL_NULL(TJSExceptionNotFound)
TJS_MSG_DECL_NULL(TJSInvalidFormatString)
TJS_MSG_DECL_NULL(TJSDivideByZero)
TJS_MSG_DECL_NULL(TJSNotReconstructiveRandomizeData)
TJS_MSG_DECL_NULL(TJSSymbol)
TJS_MSG_DECL_NULL(TJSCallHistoryIsFromOutOfTJS2Script)
TJS_MSG_DECL_NULL(TJSNObjectsWasNotFreed)
TJS_MSG_DECL_NULL(TJSObjectCreationHistoryDelimiter)
TJS_MSG_DECL_NULL(TJSObjectWasNotFreed)
TJS_MSG_DECL_NULL(TJSGroupByObjectTypeAndHistory)
TJS_MSG_DECL_NULL(TJSGroupByObjectType)
TJS_MSG_DECL_NULL(TJSObjectCountingMessageGroupByObjectTypeAndHistory)
TJS_MSG_DECL_NULL(TJSObjectCountingMessageTJSGroupByObjectType)
TJS_MSG_DECL_NULL(TJSWarnRunningCodeOnDeletingObject)
TJS_MSG_DECL_NULL(TJSWriteError)
TJS_MSG_DECL_NULL(TJSReadError)
TJS_MSG_DECL_NULL(TJSSeekError)
TJS_MSG_DECL_NULL(TJSByteCodeBroken)
TJS_MSG_DECL_NULL(TJSObjectHashMapLogVersionMismatch)
TJS_MSG_DECL_NULL(TJSCurruptedObjectHashMapLog)
TJS_MSG_DECL_NULL(TJSUnknownFailure)
TJS_MSG_DECL_NULL(TJSUnknownPackUnpackTemplateCharcter)
TJS_MSG_DECL_NULL(TJSUnknownBitStringCharacter)
TJS_MSG_DECL_NULL(TJSUnknownHexStringCharacter)
TJS_MSG_DECL_NULL(TJSNotSupportedUuencode)
TJS_MSG_DECL_NULL(TJSNotSupportedBER)
TJS_MSG_DECL_NULL(TJSNotSupportedUnpackLP)
TJS_MSG_DECL_NULL(TJSNotSupportedUnpackP)
TJS_MSG_DECL_NULL(TVPVersionInformation)
TJS_MSG_DECL_NULL(TVPVersionInformation2)
TJS_MSG_DECL_NULL(TVPDownloadPageURL)
TJS_MSG_DECL_NULL(TVPInternalError)
TJS_MSG_DECL_NULL(TVPInvalidParam)
TJS_MSG_DECL_NULL(TVPWarnDebugOptionEnabled)
TJS_MSG_DECL_NULL(TVPCommandLineParamIgnoredAndDefaultUsed)
TJS_MSG_DECL_NULL(TVPInvalidCommandLineParam)
TJS_MSG_DECL_NULL(TVPNotImplemented)
TJS_MSG_DECL_NULL(TVPCannotOpenStorage)
TJS_MSG_DECL_NULL(TVPCannotFindStorage)
TJS_MSG_DECL_NULL(TVPCannotOpenStorageForWrite)
TJS_MSG_DECL_NULL(TVPStorageInArchiveNotFound)
TJS_MSG_DECL_NULL(TVPInvalidPathName)
TJS_MSG_DECL_NULL(TVPUnsupportedMediaName)
TJS_MSG_DECL_NULL(TVPCannotUnbindXP3EXE)
TJS_MSG_DECL_NULL(TVPCannotFindXP3Mark)
TJS_MSG_DECL_NULL(TVPMissingPathDelimiterAtLast)
TJS_MSG_DECL_NULL(TVPFilenameContainsSharpWarn)
TJS_MSG_DECL_NULL(TVPCannotGetLocalName)
TJS_MSG_DECL_NULL(TVPReadError)
TJS_MSG_DECL_NULL(TVPWriteError)
TJS_MSG_DECL_NULL(TVPSeekError)
TJS_MSG_DECL_NULL(TVPTruncateError)
TJS_MSG_DECL_NULL(TVPInsufficientMemory)
TJS_MSG_DECL_NULL(TVPUncompressionFailed)
TJS_MSG_DECL_NULL(TVPCompressionFailed)
TJS_MSG_DECL_NULL(TVPCannotWriteToArchive)
TJS_MSG_DECL_NULL(TVPUnsupportedCipherMode)
TJS_MSG_DECL_NULL(TVPUnsupportedEncoding)
TJS_MSG_DECL_NULL(TVPUnsupportedModeString)
TJS_MSG_DECL_NULL(TVPUnknownGraphicFormat)
TJS_MSG_DECL_NULL(TVPCannotSuggestGraphicExtension)
TJS_MSG_DECL_NULL(TVPMaskSizeMismatch)
TJS_MSG_DECL_NULL(TVPProvinceSizeMismatch)
TJS_MSG_DECL_NULL(TVPImageLoadError)
TJS_MSG_DECL_NULL(TVPJPEGLoadError)
TJS_MSG_DECL_NULL(TVPPNGLoadError)
TJS_MSG_DECL_NULL(TVPERILoadError)
TJS_MSG_DECL_NULL(TVPTLGLoadError)
TJS_MSG_DECL_NULL(TVPInvalidImageSaveType)
TJS_MSG_DECL_NULL(TVPInvalidOperationFor8BPP)
TJS_MSG_DECL_NULL(TVPInvalidOperationFor32BPP)
TJS_MSG_DECL_NULL(TVPSpecifyWindow)
TJS_MSG_DECL_NULL(TVPSpecifyLayer)
TJS_MSG_DECL_NULL(TVPSpecifyLayerOrBitmap)
TJS_MSG_DECL_NULL(TVPCannotAcceptModeAuto)
TJS_MSG_DECL_NULL(TVPCannotCreateEmptyLayerImage)
TJS_MSG_DECL_NULL(TVPCannotSetPrimaryInvisible)
TJS_MSG_DECL_NULL(TVPCannotMovePrimary)
TJS_MSG_DECL_NULL(TVPCannotSetParentSelf)
TJS_MSG_DECL_NULL(TVPCannotMoveNextToSelfOrNotSiblings)
TJS_MSG_DECL_NULL(TVPCannotMovePrimaryOrSiblingless)
TJS_MSG_DECL_NULL(TVPCannotMoveToUnderOtherPrimaryLayer)
TJS_MSG_DECL_NULL(TVPInvalidImagePosition)
TJS_MSG_DECL_NULL(TVPCannotSetModeToDisabledOrModal)
TJS_MSG_DECL_NULL(TVPNotDrawableLayerType)
TJS_MSG_DECL_NULL(TVPSourceLayerHasNoImage)
TJS_MSG_DECL_NULL(TVPUnsupportedLayerType)
TJS_MSG_DECL_NULL(TVPNotDrawableFaceType)
TJS_MSG_DECL_NULL(TVPCannotConvertLayerTypeUsingGivenDirection)
TJS_MSG_DECL_NULL(TVPNegativeOpacityNotSupportedOnThisFace)
TJS_MSG_DECL_NULL(TVPSrcRectOutOfBitmap)
TJS_MSG_DECL_NULL(TVPBoxBlurAreaMustContainCenterPixel)
TJS_MSG_DECL_NULL(TVPBoxBlurAreaMustBeSmallerThan16Million)
TJS_MSG_DECL_NULL(TVPCannotChangeFocusInProcessingFocus)
TJS_MSG_DECL_NULL(TVPWindowHasNoLayer)
TJS_MSG_DECL_NULL(TVPWindowHasAlreadyPrimaryLayer)
TJS_MSG_DECL_NULL(TVPSpecifiedEventNeedsParameter)
TJS_MSG_DECL_NULL(TVPSpecifiedEventNeedsParameter2)
TJS_MSG_DECL_NULL(TVPSpecifiedEventNameIsUnknown)
TJS_MSG_DECL_NULL(TVPOutOfRectangle)
TJS_MSG_DECL_NULL(TVPInvalidMethodInUpdating)
TJS_MSG_DECL_NULL(TVPCannotCreateInstance)
TJS_MSG_DECL_NULL(TVPUnknownWaveFormat)
TJS_MSG_DECL_NULL(TVPCurrentTransitionMustBeStopping)
TJS_MSG_DECL_NULL(TVPTransHandlerError)
TJS_MSG_DECL_NULL(TVPTransAlreadyRegistered)
TJS_MSG_DECL_NULL(TVPCannotFindTransHander)
TJS_MSG_DECL_NULL(TVPSpecifyTransitionSource)
TJS_MSG_DECL_NULL(TVPLayerCannotHaveImage)
TJS_MSG_DECL_NULL(TVPTransitionSourceAndDestinationMustHaveImage)
TJS_MSG_DECL_NULL(TVPCannotLoadRuleGraphic)
TJS_MSG_DECL_NULL(TVPSpecifyOption)
TJS_MSG_DECL_NULL(TVPTransitionLayerSizeMismatch)
TJS_MSG_DECL_NULL(TVPTransitionMutualSource)
TJS_MSG_DECL_NULL(TVPHoldDestinationAlphaParameterIsNowDeprecated)
TJS_MSG_DECL_NULL(TVPCannotConnectMultipleWaveSoundBufferAtOnce)
TJS_MSG_DECL_NULL(TVPInvalidWindowSizeMustBeIn64to32768)
TJS_MSG_DECL_NULL(TVPInvalidOverlapCountMustBeIn2to32)
TJS_MSG_DECL_NULL(TVPCurrentlyAsyncLoadBitmap)
TJS_MSG_DECL_NULL(TVPFaildClipboardCopy)
TJS_MSG_DECL_NULL(TVPInvalidUTF16ToUTF8)
TJS_MSG_DECL_NULL(TVPInfoLoadingStartupScript)
TJS_MSG_DECL_NULL(TVPInfoStartupScriptEnded)
TJS_MSG_DECL_NULL(TVPTjsCharMustBeTwoOrFour)
TJS_MSG_DECL_NULL(TVPMediaNameHadAlreadyBeenRegistered)
TJS_MSG_DECL_NULL(TVPMediaNameIsNotRegistered)
TJS_MSG_DECL_NULL(TVPInfoRebuildingAutoPath)
TJS_MSG_DECL_NULL(TVPInfoTotalFileFoundAndActivated)
TJS_MSG_DECL_NULL(TVPErrorInRetrievingSystemOnActivateOnDeactivate)
TJS_MSG_DECL_NULL(TVPTheHostIsNotA16BitUnicodeSystem)
TJS_MSG_DECL_NULL(TVPInfoTryingToReadXp3VirtualFileSystemInformationFrom)
TJS_MSG_DECL_NULL(TVPSpecifiedStorageHadBeenProtected)
TJS_MSG_DECL_NULL(TVPInfoFailed)
TJS_MSG_DECL_NULL(TVPInfoDoneWithContains)
TJS_MSG_DECL_NULL(TVPSeparatorCRLF)
TJS_MSG_DECL_NULL(TVPSeparatorCR)
TJS_MSG_DECL_NULL(TVPDefaultFontName)
TJS_MSG_DECL_NULL(TVPCannotOpenFontFile)
TJS_MSG_DECL_NULL(TVPFontCannotBeUsed)
TJS_MSG_DECL_NULL(TVPFontRasterizeError)
TJS_MSG_DECL_NULL(TVPBitFieldsNotSupported)
TJS_MSG_DECL_NULL(TVPCompressedBmpNotSupported)
TJS_MSG_DECL_NULL(TVPUnsupportedColorModeForPalettImage)
TJS_MSG_DECL_NULL(TVPNotWindowsBmp)
TJS_MSG_DECL_NULL(TVPUnsupportedHeaderVersion)
TJS_MSG_DECL_NULL(TVPInfoTouching)
TJS_MSG_DECL_NULL(TVPAbortedTimeOut)
TJS_MSG_DECL_NULL(TVPAbortedLimitByte)
TJS_MSG_DECL_NULL(TVPFaildGlyphForDrawGlyph)
TJS_MSG_DECL_NULL(TVPLayerObjectIsNotProperlyConstructed)
TJS_MSG_DECL_NULL(TVPUnknownUpdateType)
TJS_MSG_DECL_NULL(TVPUnknownTransitionType)
TJS_MSG_DECL_NULL(TVPUnsupportedUpdateTypeTutGiveUpdate)
TJS_MSG_DECL_NULL(TVPErrorCode)
TJS_MSG_DECL_NULL(TVPUnsupportedJpegPalette)
TJS_MSG_DECL_NULL(TVPLibpngError)
TJS_MSG_DECL_NULL(TVPUnsupportedColorTypePalette)
TJS_MSG_DECL_NULL(TVPUnsupportedColorType)
TJS_MSG_DECL_NULL(TVPTooLargeImage)
TJS_MSG_DECL_NULL(TVPPngSaveError)
TJS_MSG_DECL_NULL(TVPTlgUnsupportedUniversalTransitionRule)
TJS_MSG_DECL_NULL(TVPUnsupportedColorCount)
TJS_MSG_DECL_NULL(TVPDataFlagMustBeZero)
TJS_MSG_DECL_NULL(TVPUnsupportedColorTypeColon)
TJS_MSG_DECL_NULL(TVPUnsupportedExternalGolombBitLengthTable)
TJS_MSG_DECL_NULL(TVPUnsupportedEntropyCodingMethod)
TJS_MSG_DECL_NULL(TVPInvalidTlgHeaderOrVersion)
TJS_MSG_DECL_NULL(TVPTlgMalformedTagMissionColonAfterNameLength)
TJS_MSG_DECL_NULL(TVPTlgMalformedTagMissionEqualsAfterName)
TJS_MSG_DECL_NULL(TVPTlgMalformedTagMissionColonAfterVaueLength)
TJS_MSG_DECL_NULL(TVPTlgMalformedTagMissionCommaAfterTag)
TJS_MSG_DECL_NULL(TVPFileSizeIsZero)
TJS_MSG_DECL_NULL(TVPMemoryAllocationError)
TJS_MSG_DECL_NULL(TVPFileReadError)
TJS_MSG_DECL_NULL(TVPInvalidPrerenderedFontFile)
TJS_MSG_DECL_NULL(TVPNot16BitUnicodeFontFile)
TJS_MSG_DECL_NULL(TVPInvalidHeaderVersion)
TJS_MSG_DECL_NULL(TVPTlgInsufficientMemory)
TJS_MSG_DECL_NULL(TVPTlgTooLargeBitLength)
TJS_MSG_DECL_NULL(TVPCannotRetriveInterfaceFromDrawDevice)
TJS_MSG_DECL_NULL(TVPScriptExceptionRaised)
TJS_MSG_DECL_NULL(TVPHardwareExceptionRaised)
TJS_MSG_DECL_NULL(TVPMainCDPName)
TJS_MSG_DECL_NULL(TVPExceptionCDPName)
TJS_MSG_DECL_NULL(TVPCannnotLocateUIDLLForFolderSelection)
TJS_MSG_DECL_NULL(TVPInvalidUIDLL)
TJS_MSG_DECL_NULL(TVPInvalidBPP)
TJS_MSG_DECL_NULL(TVPCannotLoadPlugin)
TJS_MSG_DECL_NULL(TVPNotValidPlugin)
TJS_MSG_DECL_NULL(TVPPluginUninitFailed)
TJS_MSG_DECL_NULL(TVPCannnotLinkPluginWhilePluginLinking)
TJS_MSG_DECL_NULL(TVPNotSusiePlugin)
TJS_MSG_DECL_NULL(TVPSusiePluginError)
TJS_MSG_DECL_NULL(TVPCannotReleasePlugin)
TJS_MSG_DECL_NULL(TVPNotLoadedPlugin)
TJS_MSG_DECL_NULL(TVPCannotAllocateBitmapBits)
TJS_MSG_DECL_NULL(TVPScanLineRangeOver)
TJS_MSG_DECL_NULL(TVPPluginError)
TJS_MSG_DECL_NULL(TVPInvalidCDDADrive)
TJS_MSG_DECL_NULL(TVPCDDADriveNotFound)
TJS_MSG_DECL_NULL(TVPMCIError)
TJS_MSG_DECL_NULL(TVPInvalidSMF)
TJS_MSG_DECL_NULL(TVPMalformedMIDIMessage)
TJS_MSG_DECL_NULL(TVPCannotInitDirectSound)
TJS_MSG_DECL_NULL(TVPCannotCreateDSSecondaryBuffer)
TJS_MSG_DECL_NULL(TVPInvalidLoopInformation)
TJS_MSG_DECL_NULL(TVPNotChildMenuItem)
TJS_MSG_DECL_NULL(TVPCannotInitDirect3D)
TJS_MSG_DECL_NULL(TVPCannotFindDisplayMode)
TJS_MSG_DECL_NULL(TVPCannotSwitchToFullScreen)
TJS_MSG_DECL_NULL(TVPInvalidPropertyInFullScreen)
TJS_MSG_DECL_NULL(TVPInvalidMethodInFullScreen)
TJS_MSG_DECL_NULL(TVPCannotLoadCursor)
TJS_MSG_DECL_NULL(TVPCannotLoadKrMovieDLL)
TJS_MSG_DECL_NULL(TVPInvalidKrMovieDLL)
TJS_MSG_DECL_NULL(TVPErrorInKrMovieDLL)
TJS_MSG_DECL_NULL(TVPWindowAlreadyMissing)
TJS_MSG_DECL_NULL(TVPPrerenderedFontMappingFailed)
TJS_MSG_DECL_NULL(TVPConfigFailOriginalFileCannotBeRewritten)
TJS_MSG_DECL_NULL(TVPConfigFailTempExeNotErased)
TJS_MSG_DECL_NULL(TVPExecutionFail)
TJS_MSG_DECL_NULL(TVPPluginUnboundFunctionError)
TJS_MSG_DECL_NULL(TVPExceptionHadBeenOccured)
TJS_MSG_DECL_NULL(TVPConsoleResult)
TJS_MSG_DECL_NULL(TVPInfoListingFiles)
TJS_MSG_DECL_NULL(TVPInfoTotalPhysicalMemory)
TJS_MSG_DECL_NULL(TVPInfoSelectedProjectDirectory)
TJS_MSG_DECL_NULL(TVPTooSmallExecutableSize)
TJS_MSG_DECL_NULL(TVPInfoLoadingExecutableEmbeddedOptionsFailed)
TJS_MSG_DECL_NULL(TVPInfoLoadingExecutableEmbeddedOptionsSucceeded)
TJS_MSG_DECL_NULL(TVPFileNotFound)
TJS_MSG_DECL_NULL(TVPInfoLoadingConfigurationFileFailed)
TJS_MSG_DECL_NULL(TVPInfoLoadingConfigurationFileSucceeded)
TJS_MSG_DECL_NULL(TVPInfoDataPathDoesNotExistTryingToMakeIt)
TJS_MSG_DECL_NULL(TVPOk)
TJS_MSG_DECL_NULL(TVPFaild)
TJS_MSG_DECL_NULL(TVPInfoDataPath)
TJS_MSG_DECL_NULL(TVPInfoSpecifiedOptionEarlierItemHasMorePriority)
TJS_MSG_DECL_NULL(TVPNone)
TJS_MSG_DECL_NULL(TVPInfoCpuClockRoughly)
TJS_MSG_DECL_NULL(TVPProgramStartedOn)
TJS_MSG_DECL_NULL(TVPKirikiri)
TJS_MSG_DECL_NULL(TVPUnknownError)
TJS_MSG_DECL_NULL(TVPExitCode)
TJS_MSG_DECL_NULL(TVPFatalError)
TJS_MSG_DECL_NULL(TVPEnableDigitizer)
TJS_MSG_DECL_NULL(TVPTouchIntegratedTouch)
TJS_MSG_DECL_NULL(TVPTouchExternalTouch)
TJS_MSG_DECL_NULL(TVPTouchIntegratedPen)
TJS_MSG_DECL_NULL(TVPTouchExternalPen)
TJS_MSG_DECL_NULL(TVPTouchMultiInput)
TJS_MSG_DECL_NULL(TVPTouchReady)
TJS_MSG_DECL_NULL(TVPCpuCheckFailure)
TJS_MSG_DECL_NULL(TVPCpuCheckFailureCpuFamilyOrLesserIsNotSupported)
TJS_MSG_DECL_NULL(TVPInfoCpuNumber)
TJS_MSG_DECL_NULL(TVPCpuCheckFailureNotSupprtedCpu)
TJS_MSG_DECL_NULL(TVPInfoFinallyDetectedCpuFeatures)
TJS_MSG_DECL_NULL(TVPCpuCheckFailureNotSupportedCpu)
TJS_MSG_DECL_NULL(TVPInfoCpuClock)
TJS_MSG_DECL_NULL(TVPLayerBitmapBufferUnderrunDetectedCheckYourDrawingCode)
TJS_MSG_DECL_NULL(TVPLayerBitmapBufferOverrunDetectedCheckYourDrawingCode)
TJS_MSG_DECL_NULL(TVPFaildToCreateDirect3D)
TJS_MSG_DECL_NULL(TVPFaildToDecideBackbufferFormat)
TJS_MSG_DECL_NULL(TVPFaildToCreateDirect3DDevice)
TJS_MSG_DECL_NULL(TVPFaildToSetViewport)
TJS_MSG_DECL_NULL(TVPFaildToSetRenderState)
TJS_MSG_DECL_NULL(TVPWarningImageSizeTooLargeMayBeCannotCreateTexture)
TJS_MSG_DECL_NULL(TVPUsePowerOfTwoSurface)
TJS_MSG_DECL_NULL(TVPCannotAllocateD3DOffScreenSurface)
TJS_MSG_DECL_NULL(TVPBasicDrawDeviceFailedToCreateDirect3DDevices)
TJS_MSG_DECL_NULL(TVPBasicDrawDeviceFailedToCreateDirect3DDevicesUnknownReason)
TJS_MSG_DECL_NULL(TVPBasicDrawDeviceTextureHasAlreadyBeenLocked)
TJS_MSG_DECL_NULL(TVPInternalErrorResult)
TJS_MSG_DECL_NULL(TVPBasicDrawDeviceInfPolygonDrawingFailed)
TJS_MSG_DECL_NULL(TVPBasicDrawDeviceInfDirect3DDevicePresentFailed)
TJS_MSG_DECL_NULL(TVPChangeDisplaySettingsFailedDispChangeRestart)
TJS_MSG_DECL_NULL(TVPChangeDisplaySettingsFailedDispChangeBadFlags)
TJS_MSG_DECL_NULL(TVPChangeDisplaySettingsFailedDispChangeBadParam)
TJS_MSG_DECL_NULL(TVPChangeDisplaySettingsFailedDispChangeFailed)
TJS_MSG_DECL_NULL(TVPChangeDisplaySettingsFailedDispChangeBadMode)
TJS_MSG_DECL_NULL(TVPChangeDisplaySettingsFailedDispChangeNotUpdated)
TJS_MSG_DECL_NULL(TVPChangeDisplaySettingsFailedUnknownReason)
TJS_MSG_DECL_NULL(TVPFailedToCreateScreenDC)
TJS_MSG_DECL_NULL(TVPFailedToCreateOffscreenBitmap)
TJS_MSG_DECL_NULL(TVPFailedToCreateOffscreenDC)
TJS_MSG_DECL_NULL(TVPInfoSusiePluginInfo)
TJS_MSG_DECL_NULL(TVPSusiePluginUnsupportedBitmapHeader)
TJS_MSG_DECL_NULL(TVPBasicDrawDeviceFailedToCreateDirect3DDevice)
TJS_MSG_DECL_NULL(TVPBasicDrawDeviceFailedToCreateDirect3DDeviceUnknownReason)
TJS_MSG_DECL_NULL(TVPCouldNotCreateAnyDrawDevice)
TJS_MSG_DECL_NULL(TVPBasicDrawDeviceDoesNotSupporteLayerManagerMoreThanOne)
TJS_MSG_DECL_NULL(TVPInvalidVideoSize)
TJS_MSG_DECL_NULL(TVPRoughVsyncIntervalReadFromApi)
TJS_MSG_DECL_NULL(TVPRoughVsyncIntervalStillSeemsWrong)
TJS_MSG_DECL_NULL(TVPInfoFoundDirect3DInterface)
TJS_MSG_DECL_NULL(TVPInfoFaild)
TJS_MSG_DECL_NULL(TVPInfoDirect3D)
TJS_MSG_DECL_NULL(TVPCannotLoadD3DDLL)
TJS_MSG_DECL_NULL(TVPNotFoundDirect3DCreate)
TJS_MSG_DECL_NULL(TVPInfoEnvironmentUsing)
TJS_MSG_DECL_NULL(TVPInfoSearchBestFullscreenResolution)
TJS_MSG_DECL_NULL(TVPInfoConditionPreferredScreenMode)
TJS_MSG_DECL_NULL(TVPInfoConditionMode)
TJS_MSG_DECL_NULL(TVPInfoConditionZoomMode)
TJS_MSG_DECL_NULL(TVPInfoEnvironmentDefaultScreenMode)
TJS_MSG_DECL_NULL(TVPInfoEnvironmentDefaultScreenAspectRatio)
TJS_MSG_DECL_NULL(TVPInfoEnvironmentAvailableDisplayModes)
TJS_MSG_DECL_NULL(TVPInfoNotFoundScreenModeFromDriver)
TJS_MSG_DECL_NULL(TVPInfoResultCandidates)
TJS_MSG_DECL_NULL(TVPInfoTryScreenMode)
TJS_MSG_DECL_NULL(TVPAllScreenModeError)
TJS_MSG_DECL_NULL(TVPInfoChangeScreenModeSuccess)
TJS_MSG_DECL_NULL(TVPSelectXP3FileOrFolder)
TJS_MSG_DECL_NULL(TVPD3dErrDeviceLost)
TJS_MSG_DECL_NULL(TVPD3dErrDriverIinternalError)
TJS_MSG_DECL_NULL(TVPD3dErrInvalidCall)
TJS_MSG_DECL_NULL(TVPD3dErrOutOfVideoMemory)
TJS_MSG_DECL_NULL(TVPD3dErrOutOfMemory)
TJS_MSG_DECL_NULL(TVPD3dErrWrongTextureFormat)
TJS_MSG_DECL_NULL(TVPD3dErrUnsuportedColorOperation)
TJS_MSG_DECL_NULL(TVPD3dErrUnsuportedColorArg)
TJS_MSG_DECL_NULL(TVPD3dErrUnsuportedAalphtOperation)
TJS_MSG_DECL_NULL(TVPD3dErrUnsuportedAlphaArg)
TJS_MSG_DECL_NULL(TVPD3dErrTooManyOperations)
TJS_MSG_DECL_NULL(TVPD3dErrConflictioningTextureFilter)
TJS_MSG_DECL_NULL(TVPD3dErrUnsuportedFactorValue)
TJS_MSG_DECL_NULL(TVPD3dErrConflictioningRenderState)
TJS_MSG_DECL_NULL(TVPD3dErrUnsupportedTextureFilter)
TJS_MSG_DECL_NULL(TVPD3dErrConflictioningTexturePalette)
TJS_MSG_DECL_NULL(TVPD3dErrNotFound)
TJS_MSG_DECL_NULL(TVPD3dErrMoreData)
TJS_MSG_DECL_NULL(TVPD3dErrDeviceNotReset)
TJS_MSG_DECL_NULL(TVPD3dErrNotAvailable)
TJS_MSG_DECL_NULL(TVPD3dErrInvalidDevice)
TJS_MSG_DECL_NULL(TVPD3dErrDriverInvalidCall)
TJS_MSG_DECL_NULL(TVPD3dErrWasStillDrawing)
TJS_MSG_DECL_NULL(TVPD3dErrDeviceHung)
TJS_MSG_DECL_NULL(TVPD3dErrUnsupportedOverlay)
TJS_MSG_DECL_NULL(TVPD3dErrUnsupportedOverlayFormat)
TJS_MSG_DECL_NULL(TVPD3dErrCannotProtectContent)
TJS_MSG_DECL_NULL(TVPD3dErrUnsupportedCrypto)
TJS_MSG_DECL_NULL(TVPD3dErrPresentStatisticsDisJoint)
TJS_MSG_DECL_NULL(TVPD3dErrDeviceRemoved)
TJS_MSG_DECL_NULL(TVPD3dOkNoAutoGen)
TJS_MSG_DECL_NULL(TVPD3dErrFail)
TJS_MSG_DECL_NULL(TVPD3dErrInvalidArg)
TJS_MSG_DECL_NULL(TVPD3dUnknownError)
TJS_MSG_DECL_NULL(TVPExceptionAccessViolation)
TJS_MSG_DECL_NULL(TVPExceptionBreakpoint)
TJS_MSG_DECL_NULL(TVPExceptionDatatypeMisalignment)
TJS_MSG_DECL_NULL(TVPExceptionSingleStep)
TJS_MSG_DECL_NULL(TVPExceptionArrayBoundsExceeded)
TJS_MSG_DECL_NULL(TVPExceptionFltDenormalOperand)
TJS_MSG_DECL_NULL(TVPExceptionFltDivideByZero)
TJS_MSG_DECL_NULL(TVPExceptionFltInexactResult)
TJS_MSG_DECL_NULL(TVPExceptionFltInvalidOperation)
TJS_MSG_DECL_NULL(TVPExceptionFltOverflow)
TJS_MSG_DECL_NULL(TVPExceptionFltStackCheck)
TJS_MSG_DECL_NULL(TVPExceptionFltUnderflow)
TJS_MSG_DECL_NULL(TVPExceptionIntDivideByZero)
TJS_MSG_DECL_NULL(TVPExceptionIntOverflow)
TJS_MSG_DECL_NULL(TVPExceptionPrivInstruction)
TJS_MSG_DECL_NULL(TVPExceptionNoncontinuableException)
TJS_MSG_DECL_NULL(TVPExceptionGuardPage)
TJS_MSG_DECL_NULL(TVPExceptionIllegalInstruction)
TJS_MSG_DECL_NULL(TVPExceptionInPageError)
TJS_MSG_DECL_NULL(TVPExceptionInvalidDisposition)
TJS_MSG_DECL_NULL(TVPExceptionInvalidHandle)
TJS_MSG_DECL_NULL(TVPExceptionStackOverflow)
TJS_MSG_DECL_NULL(TVPExceptionUnwindCconsolidate)
TJS_MSG_DECL_NULL(TVPCannotShowModalAreadyShowed)
TJS_MSG_DECL_NULL(TVPCannotShowModalSingleWindow)
TJS_MSG_DECL_NULL(TVPUnknowQtError)
#endif
