$0
Downloading distros via the command line
powershell "Invoke-WebRequest -Uri https://aka.ms/wsl-ubuntu-1604 -OutFile Ubuntu.appx -UseBasicParsing"
0
$1
Installing your distro
powershell "Add-AppxPackage .\Ubuntu.appx"
0
$2
Setup Ununtu 16.04 Unix account and password
ubuntu1604
0
