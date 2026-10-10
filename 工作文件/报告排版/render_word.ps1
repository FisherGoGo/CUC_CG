$ErrorActionPreference = 'Stop'
$reportRoot = 'D:\Project\University Session\Computer Graphics'
$reportWord = $null
$reportDoc = $null
try {
    $reportWord = New-Object -ComObject Word.Application
    $reportWord.Visible = $false
    $reportWord.DisplayAlerts = 0
    $reportDoc = $reportWord.Documents.Open((Join-Path $reportRoot '实验报告\三+四周实验报告_排版版.docx'), $false, $true)
    $reportDoc.ExportAsFixedFormat((Join-Path $reportRoot '工作文件\报告排版\formatted.pdf'), 17)
    Write-Output ('Pages: ' + $reportDoc.ComputeStatistics(2))
} finally {
    if ($null -ne $reportDoc) { $reportDoc.Close(0) }
    if ($null -ne $reportWord) { $reportWord.Quit() }
}
