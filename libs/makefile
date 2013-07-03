OUTDIR=out

all: $(OUTDIR)
	$(MAKE) -C Codebase

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	$(RM) *.o *.a *.exe

rebuild: clean all
