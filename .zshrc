export EDITOR="vim"
export VIEWER="zathura"
export TERMINAL="st"
export LATEX="xelatex"
export CC="gcc"

unsetopt beep
bindkey -e

autoload -U colors && colors
PS1="%B%{$reset_color%}[%n@%M]%/ $ "
setopt autocd

HISTSIZE=10000
SAVEHIST=10000
HISTFILE=~/.cache/zsh/history

autoload -U compinit
zstyle ':completion:*' menu select
zmodload zsh/complist
compinit
_comp_options+=(globdots)

lfcd () {
    tmp="$(mktemp)"
    lf -last-dir-path="$tmp" "$@"
    if [ -f "$tmp" ]; then
        dir="$(cat "$tmp")"
        rm -f "$tmp"
        [ -d "$dir" ] && [ "$dir" != "$(pwd)" ] && cd "$dir"
    fi
}
bindkey -s '^o' 'lfcd\n'

