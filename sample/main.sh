#!/bin/sh

# grid frequency model sample.
#
# Copyright (C) 2017  Ken-ichi Kondo.
#
# This file is part of SGFM.
# 
# SGFM is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# SGFM is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with SGFM.  If not, see <http://www.gnu.org/licenses/>.


dname_this=`dirname $0`
dpath_this=`cd ${dname_this};pwd`
dthis_run=${dpath_this}
dthis_etc=`cd ${dpath_this}/../etc;pwd`
dthis_data=`cd ${dpath_this}/../data;pwd`
dthis_bin=`cd ${dpath_this}/../bin;pwd`

${dthis_bin}/main init 2 1 1 ${dthis_etc}/test

${dthis_bin}/main mod EDC 0 ${dthis_etc}/test
${dthis_bin}/main mod EDC 1 ${dthis_etc}/test
${dthis_bin}/main mod BASE 0 ${dthis_etc}/test
${dthis_bin}/main mod LOAD 0 ${dthis_etc}/test

rm -f ${dthis_data}/result.txt
${dthis_bin}/main run ${dthis_etc}/test ${dthis_data}/out1 > ${dthis_data}/result.txt
for num in `seq 1 9`
do
	numnext=`expr ${num} + 1`
	${dthis_bin}/main run ${dthis_data}/out${num} ${dthis_data}/out${numnext} | tail -n +2 >> ${dthis_data}/result.txt
done

