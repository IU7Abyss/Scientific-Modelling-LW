#!/bin/bash

cd `dirname "$0"`

INITIAL_DATA="../input/data4.csv"
TABLE_I_T0_N="../input/table_I_T0_n.csv"
TABLE_T_SIGMA="../input/table_T_Sigma.csv"

../scripts/run.sh "$INITIAL_DATA" "$TABLE_I_T0_N" "$TABLE_T_SIGMA"