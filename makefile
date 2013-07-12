OUTDIR=out

#CXXFLAGS+=-DTILE_THIN

export

all: $(OUTDIR)
	$(MAKE) -C src

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	$(RM) *.o *.a *.exe

rebuild: clean all
