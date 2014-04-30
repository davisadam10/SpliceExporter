
#include <FabricSplice.h>
#include <cstring>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace FabricSplice;

int main(int argc, const char * argv[]) 
{
  
  if(argc !=3)
  {
    printf("ERROR: Need To Pass The Operator Path And The AlembicCahce Paths\n");
    return 1;
  }

  std::string klFilePath = realpath(argv[1],0);
  std::string outputPath = argv[2];

  std::ifstream klFile(klFilePath.c_str());
  if(!klFile.good())
  {
    printf("InValid File Path - File Does Not Exist");
    return 1;
  }
  
  std::string klCode;
  std::string temp;
  while(std::getline(klFile, temp)) {
      klCode+=temp;
  }

  Initialize();
  
  //Create a KL parser
  KLParser parser = KLParser::getParser("MyParser", "MyParser", klCode.c_str());
  
  
  bool foundEntry = false;
  //Go over all of the operators in the kl file
  for (unsigned int i = 0; i<=parser.getNbKLOperators(); i++)
  {
  	//Look for the the main function within the operator
  	KLParser::KLOperator mainOperator = parser.getKLOperator(i);
  	if (std::strcmp(mainOperator.name(), "entry") == 0)
  	{
  		foundEntry = true;
		try
	  	{
		    // create the first graph
		    DGGraph graph("SpliceExportGraph");

		    // create the first DGNode
		    graph.constructDGNode("SpliceExportNode");

		    //For all of the arguments to the operator
		    KLParser::KLArgumentList args = mainOperator.arguments();
		    for(unsigned int count=0; count<args.nbArgs(); count++)
		    {
				//Add a dgNode member of the correspondin name, and type 
				graph.addDGNodeMember(args.name(count), args.type(count),FabricCore::Variant(), "SpliceExportNode");
				
				//Create a port with the correct name, and port mode
				if (std::strcmp(args.mode(count), "in") == 0)
				{
					DGPort port = graph.addDGPort(args.name(count), args.name(count), Port_Mode_IO);
				}
				else if (std::strcmp(args.mode(count), "out") == 0)
				{
					DGPort port = graph.addDGPort(args.name(count), args.name(count), Port_Mode_OUT);
				}
				else
				{
					DGPort port = graph.addDGPort(args.name(count), args.name(count), Port_Mode_IO);	
				}
				
		    }

		    // setup the kl code
		    graph.constructKLOperator("entry", klCode.c_str());

		    // evaluate the graph
		    //graph.evaluate();
		    graph.saveToFile(outputPath.c_str());	    
		}

	  	catch(Exception e)
		{
	  		printf("%s\n", e.what());
			return 1;
		}
  	}
  }

  if (foundEntry != true)
  {
  	printf("No operator called 'entry' found");
	return 1;
  }
  
  Finalize();
  return 0;
}