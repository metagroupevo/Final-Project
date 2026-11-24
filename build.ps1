$compilerDirectory = "C:\msys64\ucrt64\bin"
$compiler = Join-Path $compilerDirectory "g++.exe"

if (-not (Test-Path -LiteralPath $compiler)) {
    Write-Error "MSYS2 g++ was not found at $compiler"
    exit 1
}

# The compiler backend needs DLL files from this directory at compile and run time.
$env:PATH = $compilerDirectory + ";" + $env:PATH

& $compiler -std=c++17 -Wall -Wextra -pedantic `
    src/main.cpp src/input.cpp src/modules.cpp src/search.cpp `
    -Iinclude -o smart_city.exe

if ($LASTEXITCODE -ne 0) {
    Write-Error "Compilation failed."
    exit $LASTEXITCODE
}

Write-Host "Build succeeded: smart_city.exe"
Write-Host "Run it in this PowerShell window with: .\smart_city.exe"
