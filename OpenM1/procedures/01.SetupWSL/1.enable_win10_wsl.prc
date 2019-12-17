$0
Enable Microsoft Windows Subsystem Linux
powershell "start-process -FilePath \"powershell\" -verb runas -ArgumentList \"Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux\""
0
