# shows navigable menu of all options when hitting tab
Set-PSReadlineKeyHandler -Key Tab -Function MenuComplete

# autosuggestion
Set-PSReadLineOption -PredictionSource History
Set-PSReadLineOption -Colors @{InlinePrediction = '#7F969B'}

# aliases
function .. { cd .. }
function ... { cd ../.. }
function .... { cd ../../.. }
function ~ { cd ~ }
function gs { git status }
function gf { git fetch }
function glo { git log --oneline }
function gca { git commit -a }
function gcf { git commit -m "fixup" }
function gcaf { git commit -a -m "fixup" }
function gri2 { git rebase -i HEAD~2 }
function gri3 { git rebase -i HEAD~3 }
function wttr { curl v2.wttr.in/75082?u }
function wttr-moon { curl www.wttr.in/moon }
function pwsh { . 'C:\Program Files\PowerShell\7\pwsh.exe'}
function firefox { . 'C:\Program Files\Mozilla Firefox\firefox.exe' }
function chrome { . 'C:\Program Files\Google\Chrome\Application\chrome.exe' }
function gx { . 'C:\Users\cdapprich\AppData\Local\Programs\Opera GX\launcher.exe' }

# oh-my-posh prompt
oh-my-posh init pwsh --config 'spaceship' | Invoke-Expression

# Import the Chocolatey Profile that contains the necessary code to enable
# tab-completions to function for `choco`.
# Be aware that if you are missing these lines from your profile, tab completion
# for `choco` will not function.
# See https://ch0.co/tab-completion for details.
$ChocolateyProfile = "$env:ChocolateyInstall\helpers\chocolateyProfile.psm1"
if (Test-Path($ChocolateyProfile)) {
  Import-Module "$ChocolateyProfile"
}
