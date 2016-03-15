# COMMON
export PS1="\[\033[36m\]\u\[\033[m\]@\[\033[32m\]\h:\[\033[33;1m\]\w\[\033[m\]\$ "
export LSCOLORS=exfxbxdxcxegedabagacad

alias u='cd ..'
alias grep='grep --color=auto'

# Titre des onglets (iTerm2)
export PROMPT_COMMAND='echo -ne "\033]0;${PWD/#$HOME/~}\007"'

# For OS X : -G, for Ubuntu --color=auto
alias ls='ls -GF'
alias ll='ls -lAthGF'
alias la='ls -AGF'
#
# SSH TMP
alias sshtmp='ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no'
alias scptmp='scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no'
