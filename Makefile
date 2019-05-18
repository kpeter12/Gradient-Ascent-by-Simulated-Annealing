#
greedy:     SumofGaussians.cpp SumofGaussians.h greedy.cpp sa.cpp
	g++ -o greedy greedy.cpp SumofGaussians.cpp SumofGaussians.h
	g++ -o sa sa.cpp SumofGaussians.cpp SumofGaussians.h

clean:
	rm -f greedy
	rm -f sa
	rm -f *.o
