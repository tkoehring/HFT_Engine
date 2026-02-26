param(
    [Parameter(Mandatory=$true)]
    [string]$Command
)

$Platform = "x64"   # change if you ever add ARM
$Config = "debug"   # default config

function Run-Build($preset) {
    cmake --build --preset $preset
}

function Run-Test($preset) {
    ctest --preset $preset
}

switch ($Command) {

    "build" {
        Run-Build "$Platform-$Config"
    }

    "build-verbose" {
        Run-Build "$Platform-$Config-verbose"
    }

    "test" {
        Run-Test "$Platform-$Config"
    }

    "test-fast" {
        Run-Test "$Platform-$Config-fast"
    }

    "test-verbose" {
        Run-Test "$Platform-$Config-verbose"
    }

    "asan" {
        Run-Test "linux-debug-asan"
    }

    "format" {
        $root = (Resolve-Path "$PSScriptRoot\..").Path

        $exclude = @("\out\", "\.vs\", "\vcpkg_installed\", "\build\", "\cmake-build-")
        $files = Get-ChildItem -Path $root -Recurse -File -Include *.cpp,*.cc,*.cxx,*.h,*.hpp,*.hh |
            Where-Object {
                $p = $_.FullName
                -not ($exclude | ForEach-Object { $p -like "*$_*" } | Where-Object { $_ } )
            }

        Write-Host "clang-format: formatting $($files.Count) files..."
        foreach ($f in $files) {
            Write-Host "  $($f.FullName)"
            clang-format -i $f.FullName
        }
    }

    "tidy" {
        $buildDir = "out/build/x64-debug"

        $files = @()
        $files += Get-ChildItem -Path "src"   -Recurse -File -Include *.cpp,*.cc,*.cxx
        $files += Get-ChildItem -Path "tests" -Recurse -File -Include *.cpp,*.cc,*.cxx

        foreach ($file in $files) {
            Write-Host "Checking $($file.FullName)..."

            # Capture *all* output (clang-tidy + clang frontend).
            $out = & clang-tidy $file.FullName -p $buildDir 2>&1

            # Drop the noisy frontend summary lines (keep real diagnostics).
            $out = $out | Where-Object { $_ -notmatch '^\d+\s+warnings generated\.$' }

            # Print remaining diagnostics, if any.
            if ($out.Count -gt 0) {
                $out | ForEach-Object { Write-Host $_ }
            }
        }
    }

    default {
        Write-Host "Unknown command: $Command"
        exit 1
    }
}