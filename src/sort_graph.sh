#!/bin/bash
if [ ${1%/*} != ${1##*/} ]
then
    sort -k 1n,1 -k 2n,2 $1 > ${1%/*}/copi_${1##*/}
    echo ${1%/*}/copi_${1##*/}
else
    sort -k 1n,1 -k 2n,2 $1 > copi_${1##*/}
    echo copi_${1##*/}
fi