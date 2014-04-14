
#include <FabricSplice.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace FabricSplice;

int main(int argc, const char * argv[]) 
{
  
  if(argc !=4)
  {
    printf("ERROR: Need To Pass The Operator Path And The AlembicCahce Paths\n");
    return 1;
  }



  std::string klFilePath = realpath(argv[1],0);
  std::string alemicCachePath = realpath(argv[2],0);
  std::string outputPath = argv[3];

  std::ifstream klFile(klFilePath.c_str());
  std::ifstream abcFile(alemicCachePath.c_str());
  if(!klFile.good() || !abcFile.good())
  {
    printf("In Valid File Path Provided - File Does Not Exist");
    return 1;
  }
  
  std::string klCode;
  std::string temp;
  while(std::getline(klFile, temp)) {
      klCode+=temp;
  }

  Initialize();
  
  KLParser parser = KLParser::getParser("MyParser", "MyParser", klCode.c_str());



  try
  {
    // create the first graph
    DGGraph graph("SpliceExportGraph");

    // create the first DGNode
    graph.constructDGNode("SpliceExportNode");

    graph.addDGNodeMember("myOutMesh", "PolygonMesh",FabricCore::Variant(), "SpliceExportNode");
    graph.addDGNodeMember("alembicCachePath", "String",FabricCore::Variant(), "SpliceExportNode");
    graph.addDGNodeMember("spacing", "Integer",FabricCore::Variant(), "SpliceExportNode");
    graph.addDGNodeMember("numberOfCopies", "Integer",FabricCore::Variant(), "SpliceExportNode");

    DGPort outMeshPort = graph.addDGPort("myOutMesh", "myOutMesh", Port_Mode_IO);
    DGPort spacingPort = graph.addDGPort("spacing", "spacing", Port_Mode_IN);
    DGPort numCopiesPort = graph.addDGPort("numberOfCopies", "numberOfCopies", Port_Mode_IN);
    DGPort abcCachePathPort = graph.addDGPort("alembicCachePath", "alembicCachePath", Port_Mode_IN);

    spacingPort.setJSON("2");
    numCopiesPort.setJSON("4");
    abcCachePathPort.setVariant(FabricCore::Variant::CreateString(alemicCachePath.c_str()));

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
  
  Finalize();
  return 0;
}