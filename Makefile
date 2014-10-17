SOURCE=floor2.cc
SOURCE2=controller2.cc
SOURCE3=object2.cc
SOURCE4=display2.cc
MYPROGRAM=cc3k

CC=g++

all: $(MYPROGRAM)


$(MYPROGRAM): $(SOURCE) $(SOURCE2) $(SOURCE3) $(SOURCE4)

	$(CC)  $(SOURCE)  $(SOURCE2) $(SOURCE3) $(SOURCE4) -o $(MYPROGRAM)


clean:

	rm -f $(MYPROGRAM)

