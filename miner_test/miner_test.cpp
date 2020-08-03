#include <iostream>
#include <stratum_client.h>

int main(int argc, char* argv[])
{
	try
	{
		stratum::stratum_client sc("pool.supportxmr.com", "3333", 
			"43F9z3PGSgBacfTwbGrw3DG65VDNT38N8XBnVjVrDo9uA5wpQnSvnYHB9wYZBxMXk6DYUf9aVxjTxFwyrXKVScRk9vD4kgC", 
			"x");
		system("pause");
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}
	return 0;
}
