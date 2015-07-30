#!/usr/bin/zsh

smartfzf_path=$(echo "$(cd "$(dirname "$0")";pwd -P)/../build/smartfzf"\
    | sed "s/[^/]\+\/..\///")
# don't kill me for using regex logan, the
# code above only executes once
# and also it won't be needed once
# we finish the thing

if [ -x $smartfzf_path ]; then
    echo  -n "Found smartfzf at "
    echo $smartfzf_path
else
    >&2 echo "Error: smartfzf not found"
fi

function _run_smartfzf {
    zle -M "`ls | $smartfzf_path $BUFFER`"
}
zle -N _run_smartfzf
bindkey '^[[2~' _run_smartfzf # on my debian this is insert
bindkey '^[[1;5C' _run_smartfzf # on my debian this is ctrl+rightarrow
bindkey '^[[5C' _run_smartfzf # this SHOULD be ctrl+rightarrow on macbooks
                              # but I haven't tested it
