#!/bin/bash

cd `dirname "$0"`

ROOT=".."

IN_DIR="input"
OUT_DIR="output"

GNUPLOT_SCRIPT="${ROOT}/scripts/graphs.gnuplot"

IN_INTIAL="$1" # initial value
IN_TABLE1="$2" # table | I | T0 | n |
IN_TABLE2="$3" # table | T | Sigma |

# mkdir for model
MODELS_DIR="models"
CURENT_MODEL_DIR="${ROOT}/${MODELS_DIR}/`date "+%Y-%m-%d_%H-%M-%S"`"

mkdir -p $CURENT_MODEL_DIR;

# make structure
CURENT_MODEL_INPUT_DIR="${CURENT_MODEL_DIR}/${IN_DIR}"
CURENT_MODEL_OUTPUT_DIR="${CURENT_MODEL_DIR}/${OUT_DIR}"

mkdir -p "$CURENT_MODEL_INPUT_DIR" "$CURENT_MODEL_OUTPUT_DIR";

# copy input data
INITIAL_DATA="data.csv"
TABLE_I_T0_N="I_T0_n.csv"
TABLE_T_SIGMA="T_Sigma.csv"

cp "$IN_INTIAL" "${CURENT_MODEL_INPUT_DIR}/${INITIAL_DATA}" &
cp "$IN_TABLE1" "${CURENT_MODEL_INPUT_DIR}/${TABLE_I_T0_N}" &
cp "$IN_TABLE2" "${CURENT_MODEL_INPUT_DIR}/${TABLE_T_SIGMA}" &
wait

#
OUT_RUNGE4="${CURENT_MODEL_OUTPUT_DIR}/runge4.csv"
OUT_TRAPEZIUM="${CURENT_MODEL_OUTPUT_DIR}/trapezium.csv"
OUT_IMG="${CURENT_MODEL_OUTPUT_DIR}/graphs.png"

"${ROOT}"/ode "${CURENT_MODEL_INPUT_DIR}/${INITIAL_DATA}" \
         "${CURENT_MODEL_INPUT_DIR}/${TABLE_I_T0_N}" \
         "${CURENT_MODEL_INPUT_DIR}/${TABLE_T_SIGMA}" \
         "${OUT_RUNGE4}" \
         "${OUT_TRAPEZIUM}";
echo Plotting graphs...
gnuplot -e "filename='${OUT_IMG}'; runge4_data='${OUT_RUNGE4}'; trapezium_data='${OUT_TRAPEZIUM}'" \
		"$GNUPLOT_SCRIPT"
echo Plotting completed.