Write-Host "Cleaning build files"
Remove-Item -Recurse -Force "out"
Remove-Item -Recurse -Force "CMakeFiles"
Remove-Item -Force "CMakeCache.txt"
