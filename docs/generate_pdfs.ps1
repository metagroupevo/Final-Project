param()

$ErrorActionPreference = 'Stop'

$chrome = 'C:\Program Files\Google\Chrome\Application\chrome.exe'
if (-not (Test-Path -LiteralPath $chrome)) {
    $chrome = 'C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe'
}

function Convert-InlineMarkdown([string]$text) {
    $encoded = [System.Net.WebUtility]::HtmlEncode($text)
    $encoded = [regex]::Replace($encoded, '`([^`]+)`', '<code>$1</code>')
    $encoded = [regex]::Replace($encoded, '\*\*([^*]+)\*\*', '<strong>$1</strong>')
    $encoded = [regex]::Replace($encoded, '\*([^*]+)\*', '<em>$1</em>')
    return $encoded
}

function Convert-MarkdownToHtml([string]$markdown, [string]$title) {
    $lines = $markdown -split "`r?`n"
    $body = [System.Text.StringBuilder]::new()
    $inCode = $false
    $code = [System.Text.StringBuilder]::new()
    $inList = $false
    $listType = ''

    function Close-List {
        if ($inList) {
            [void]$body.AppendLine("</$listType>")
            Set-Variable -Name inList -Value $false -Scope 1
            Set-Variable -Name listType -Value '' -Scope 1
        }
    }

    for ($i = 0; $i -lt $lines.Count; $i++) {
        $line = $lines[$i]

        if ($line -match '^```') {
            Close-List
            if ($inCode) {
                [void]$body.AppendLine('<pre><code>' + [System.Net.WebUtility]::HtmlEncode($code.ToString().TrimEnd()) + '</code></pre>')
                $code.Clear() | Out-Null
                $inCode = $false
            } else {
                $inCode = $true
            }
            continue
        }

        if ($inCode) {
            [void]$code.AppendLine($line)
            continue
        }

        if ($line -match '^\|.*\|$' -and $i + 1 -lt $lines.Count -and $lines[$i + 1] -match '^\|[\s:|-]+\|$') {
            Close-List
            $headers = $line.Trim('|').Split('|') | ForEach-Object { $_.Trim() }
            $i += 2
            [void]$body.AppendLine('<table><thead><tr>')
            foreach ($header in $headers) { [void]$body.AppendLine('<th>' + (Convert-InlineMarkdown $header) + '</th>') }
            [void]$body.AppendLine('</tr></thead><tbody>')
            while ($i -lt $lines.Count -and $lines[$i] -match '^\|.*\|$') {
                $cells = $lines[$i].Trim('|').Split('|') | ForEach-Object { $_.Trim() }
                [void]$body.AppendLine('<tr>')
                foreach ($cell in $cells) { [void]$body.AppendLine('<td>' + (Convert-InlineMarkdown $cell) + '</td>') }
                [void]$body.AppendLine('</tr>')
                $i++
            }
            [void]$body.AppendLine('</tbody></table>')
            $i--
            continue
        }

        if ($line -match '^(#{1,4})\s+(.+)$') {
            Close-List
            $level = $Matches[1].Length
            [void]$body.AppendLine("<h$level>$(Convert-InlineMarkdown $Matches[2])</h$level>")
        } elseif ($line -match '^\s*[-*]\s+(.+)$') {
            if (-not $inList -or $listType -ne 'ul') { Close-List; [void]$body.AppendLine('<ul>'); $inList = $true; $listType = 'ul' }
            [void]$body.AppendLine('<li>' + (Convert-InlineMarkdown $Matches[1]) + '</li>')
        } elseif ($line -match '^\s*\d+\.\s+(.+)$') {
            if (-not $inList -or $listType -ne 'ol') { Close-List; [void]$body.AppendLine('<ol>'); $inList = $true; $listType = 'ol' }
            [void]$body.AppendLine('<li>' + (Convert-InlineMarkdown $Matches[1]) + '</li>')
        } elseif ([string]::IsNullOrWhiteSpace($line)) {
            Close-List
        } else {
            Close-List
            [void]$body.AppendLine('<p>' + (Convert-InlineMarkdown $line) + '</p>')
        }
    }
    Close-List

    return @"
<!doctype html>
<html><head><meta charset="utf-8"><title>$([System.Net.WebUtility]::HtmlEncode($title))</title>
<style>
@page { size: A4; margin: 18mm 16mm 20mm; }
* { box-sizing: border-box; }
body { color: #18212f; font-family: "Segoe UI", Arial, sans-serif; font-size: 10.5pt; line-height: 1.5; }
h1 { color: #123a63; font-size: 25pt; border-bottom: 3px solid #2b78b8; padding-bottom: 8px; margin: 0 0 24px; }
h2 { color: #18578c; font-size: 16pt; margin: 24px 0 8px; page-break-after: avoid; }
h3 { color: #286b9c; font-size: 12.5pt; margin: 18px 0 6px; page-break-after: avoid; }
h4 { color: #365b76; font-size: 11pt; page-break-after: avoid; }
p { margin: 6px 0 10px; }
ul, ol { margin: 5px 0 12px 22px; padding: 0; }
li { margin: 3px 0; }
code { background: #eef3f7; border-radius: 3px; font-family: Consolas, monospace; padding: 1px 4px; }
pre { background: #152536; color: #eef6ff; border-radius: 6px; padding: 12px; overflow-wrap: anywhere; white-space: pre-wrap; page-break-inside: avoid; }
pre code { background: transparent; padding: 0; }
table { width: 100%; border-collapse: collapse; margin: 12px 0 18px; font-size: 8.7pt; page-break-inside: auto; }
thead { display: table-header-group; }
tr { page-break-inside: avoid; }
th { background: #18578c; color: white; text-align: left; }
th, td { border: 1px solid #b7c6d4; padding: 6px 7px; vertical-align: top; overflow-wrap: anywhere; }
tbody tr:nth-child(even) { background: #f3f7fa; }
</style></head><body>$body</body></html>
"@
}

$documents = @(
    @{ Source = 'TECHNICAL_MANUAL.md'; Output = 'Technical_Manual.pdf'; Title = 'Technical Manual' },
    @{ Source = 'ARCHITECTURE.md'; Output = 'System_Architecture.pdf'; Title = 'System Architecture' },
    @{ Source = 'TESTING_REPORT.md'; Output = 'Test_Report.pdf'; Title = 'Testing and Peer Code Audit Report' }
)

$docsDirectory = $PSScriptRoot
$temporaryDirectory = Join-Path ([System.IO.Path]::GetTempPath()) ('smart-city-pdf-' + [guid]::NewGuid())
New-Item -ItemType Directory -Path $temporaryDirectory | Out-Null

try {
    foreach ($document in $documents) {
        $sourcePath = Join-Path $docsDirectory $document.Source
        $htmlPath = Join-Path $temporaryDirectory ($document.Output -replace '\.pdf$', '.html')
        $outputPath = Join-Path $docsDirectory $document.Output
        $markdown = Get-Content -LiteralPath $sourcePath -Raw -Encoding UTF8
        $html = Convert-MarkdownToHtml $markdown $document.Title
        [System.IO.File]::WriteAllText($htmlPath, $html, [System.Text.UTF8Encoding]::new($false))
        $fileUri = ([uri]$htmlPath).AbsoluteUri
        & $chrome --headless --disable-gpu --no-pdf-header-footer "--print-to-pdf=$outputPath" $fileUri | Out-Null
        if ($LASTEXITCODE -ne 0 -or -not (Test-Path -LiteralPath $outputPath)) {
            throw "Failed to generate $($document.Output)"
        }
        Write-Host "Generated $outputPath"
    }
} finally {
    Remove-Item -LiteralPath $temporaryDirectory -Recurse -Force -ErrorAction SilentlyContinue
}
