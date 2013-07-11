OUTDIR=out

all: $(OUTDIR)
	$(MAKE) -C src

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	$(RM) *.o *.a *.exe

rebuild: clean all
