JAVAC = javac
JAVA = java

all: compile

compile:
	$(JAVAC) Server.java
	$(JAVAC) Client.java

run-server:
	$(JAVA) Server

run-client:
	$(JAVA) Client

clean:
	rm -f *.class

.PHONY: all compile run-server run-client clean
