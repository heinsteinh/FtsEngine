// xmlFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#undef LIBXML_ICONV_ENABLED

#pragma comment(lib, "libxml2.lib")
#pragma comment(lib, "iconv.lib")


#include <libxml/parser.h>
#include <libxml/tree.h>


#include <cassert>

#include "XMLNode.h"
#include "XMLUtils.h"

//https://github.com/artcom/mobile-spark/tree/6acd2c2b2f6fb4d0addda28ab27f5fa544698615/core/src/masl

//#define ENSURE_FULL(EXPRESSION, MESSAGE, EXPECT) ensure(EXPRESSION, MESSAGE, __FILE__, __LINE__, EXPECT);
//
//#define ENSURE_MSG(EXP, MSG) ENSURE_FULL(EXP,MSG ,true );
//#define ENSURE(EXP) ENSURE_FULL(EXP,#EXP,true );
//#define ENSURE_FAIL_EXPECTED(EXP) ENSURE_FULL(EXP,#EXP,false);
//
//#define FAILURE(MSG) ENSURE_FULL(false,MSG,true );
//#define FAILURE_EXPECTED(MSG) ENSURE_FULL(false,MSG,false);
//#define SUCCESS(MSG) ENSURE_FULL(true ,MSG,true );
//
//#define ENSURE_EXCEPTION(theTest, theException) \
//{ \
//	try {\
//	theTest; \
//	FAILURE(#theTest) \
//	}catch (const theException &) {\
//		SUCCESS(#theTest) \
//	} \
//}

int _tmain(int argc, _TCHAR* argv[])
{



	xmlDocPtr doc = masl::loadXML("/sdcard/test.spark");
	
	xmlNode* xmlLibNode = xmlDocGetRootElement(doc);
	
	masl::XMLNode *myXMLNode = new masl::XMLNode(xmlLibNode);	
	masl::XMLNodePtr myXMLNode2(new masl::XMLNode(xmlLibNode));
	
		
	
	assert(myXMLNode2->attributes.find("width") != myXMLNode2->attributes.end());
	assert(myXMLNode2->attributes["width"]== std::string("300"));

	xmlFreeDoc(doc);

	return 0;
}

