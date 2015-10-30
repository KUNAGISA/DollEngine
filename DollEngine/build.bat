cd %~dp0
rd /s /q build-DollEngine-Desktop_Qt_5_5_0_MinGW_32bit-Debug\debug\data
md build-DollEngine-Desktop_Qt_5_5_0_MinGW_32bit-Debug\debug\data
xcopy DollEngine\Resource\data build-DollEngine-Desktop_Qt_5_5_0_MinGW_32bit-Debug\debug\data /s /y