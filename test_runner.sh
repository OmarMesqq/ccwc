#!/bin/bash
set -uo pipefail

make release

# Helper function to normalize output based on OS
# macOS 'wc' pads with spaces (usually 8 chars wide for the number)
# Linux 'wc' does not. This mimics the macOS padding on Linux.
normalize_wc() {
    local input="$1"
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # On Linux: Use printf to add the 8-character padding macOS uses
        # This takes "342190 test.txt" and makes it "  342190 test.txt"
        printf "%8s %s" $(echo "$input")
    else
        # On macOS: Keep it exactly as is
        printf '%s' "$input"
    fi
}

echo "Step 1 (-c option): number of bytes"
WC_CMD_1=$(normalize_wc "$(wc -c test.txt)")
CCWC_CMD_1=$(normalize_wc "$(./ccwc -c test.txt)")

WC_CMD_2=$(normalize_wc "$(wc -c utf8_peq.txt)")
CCWC_CMD_2=$(normalize_wc "$(./ccwc -c utf8_peq.txt)")

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Step 2 (-l option): number of lines"
WC_CMD_1=$(normalize_wc "$(wc -l test.txt)")
CCWC_CMD_1=$(normalize_wc "$(./ccwc -l test.txt)")

WC_CMD_2=$(normalize_wc "$(wc -l utf8_peq.txt)")
CCWC_CMD_2=$(normalize_wc "$(./ccwc -l utf8_peq.txt)")

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Step 3 (-w option): number of words"
WC_CMD_1=$(normalize_wc "$(wc -w test.txt)")
CCWC_CMD_1=$(normalize_wc "$(./ccwc -w test.txt)")

WC_CMD_2=$(normalize_wc "$(wc -w utf8_peq.txt)")
CCWC_CMD_2=$(normalize_wc "$(./ccwc -w utf8_peq.txt)")

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Step 4 (-m option): number of characters"
WC_CMD_1=$(normalize_wc "$(wc -m test.txt)")
CCWC_CMD_1=$(normalize_wc "$(./ccwc -m test.txt)")

WC_CMD_2=$(normalize_wc "$(wc -m utf8_peq.txt)")
CCWC_CMD_2=$(normalize_wc "$(./ccwc -m utf8_peq.txt)")

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Step 5: no flags"
WC_CMD_1=$(normalize_wc "$(wc test.txt)")
CCWC_CMD_1=$(normalize_wc "$(./ccwc test.txt)")

WC_CMD_2=$(normalize_wc "$(wc utf8_peq.txt)")
CCWC_CMD_2=$(normalize_wc "$(./ccwc utf8_peq.txt)")

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Final Step: read from stdin if no filename specified"
WC_CMD_1=$(normalize_wc "$(cat test.txt | wc -l)")
CCWC_CMD_1=$(normalize_wc "$(cat test.txt | ./ccwc -l)")

WC_CMD_2=$(normalize_wc "$(cat utf8_peq.txt | wc -c)")
CCWC_CMD_2=$(normalize_wc "$(cat utf8_peq.txt | ./ccwc -c)")

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

# echo "Comparing utf8_peq.txt"
# printf '%s' "$WC_CMD_2"
# echo ""
# printf '%s' "$CCWC_CMD_2"
# echo ""

# cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
# case $? in
#  0) ;;
#  1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
#  *) echo "ERROR when comparing outputs"; exit 1 ;;
# esac

echo "SUCCESS! All tests passed."