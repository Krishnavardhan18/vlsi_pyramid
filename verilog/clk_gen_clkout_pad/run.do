xvlog -sv -f tb.f
xelab tb -s sim
xsim sim --gui
add_wave *
run all