SKETCH=6502_monitor

install_cu:
	cp ../simulator/src/addrmodes.h $(SKETCH)/addrmodes.h
	perl -pi -e's/C[12345]\.//g' $(SKETCH)/addrmodes.h
	cp ../simulator/src/ops.h $(SKETCH)/ops.h
	perl -pi -e's/C[12345]\.//g' $(SKETCH)/ops.h