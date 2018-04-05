//#include <iostream>
//using namespace std;
//#include <string.h>
//#include "tagset.h"


//int ClTagset::tagIstErlaubt(
//        char *name)
//{
//    for (int i=0;i<anzahlTags;i++)
//        if (!strcmp(name,tagNamen[i]))
//            return i;

//    return -1;
//}


//ClTagset::ClTagset(
//        int ntags,
//        int natt,
//        char **tags,
//        char **atts)
//{
//    int i;

//    anzahlTags=ntags;
//    tagNamen=new char *[ntags];

//    anzahlAttribute =  natt;
//    attNamen= new char *[natt];

//    for (i=0;i<ntags;i++)
//    {
//        tagNamen[i]=new char[64];
//        strcpy(tagNamen[i],tags[i]);
//    }

//    for (i=0;i<natt;i++)
//    {
//        attNamen[i]=new char[64];
//        strcpy(attNamen[i],atts[i]);
//    }

//    child=new ClTagset *[ntags];
//    for (i=0;i<ntags;i++)
//        child[i]=NULL;
//}


//void ClTagset::addTagset(
//        int ntags,
//        int natt,
//        int slot,
//        char **tags,
//        char **atts)
//{
//    child[slot]=new ClTagset(ntags, natt, tags, atts);
//}


////char *elemente1[1] = {"kurs"};
////char *elemente2[1] = {"person"};
////char *elemente3[2] = {"vorname","famname"};

////ClTagset *tagset, *child;

////tagset=new ClTagset(1,elemente1);
//        /* ==> tagset:
//        anzahlTags==1

//            **tagNamen == *tagNamen[1] (new char Array Pointer der Länge 1)
//            tagNamen[0]=new char[64]
//            tagNamen[0]= element1[0]=="kurs"

//        tagNamen[0]=="kurs"

//            ClTagset **child == new *child[1] (new ClTagset Array Pointer der Länge 1)      (tagset->*child[1])

//        child[0] == NULL; (ClTagset Objekt an der Stelle des ClTagset-Arrays "child[]" an der Stelle child[0] NULL setzen)

//        */

////tagset->addTagset(1,0,elemente2);
//        /* ==> tagset->child[0]

//        tagset->child[0] = new ClTagset(1, element2)

//            anzahlTags == 1

//                **tagNamen == *tagNamen[1] (new char Array Pointer der Länge 1)
//                tagNamen[0]=new char[64]
//                tagNamen[0]= element2[0]=="person"

//            tagNamen[0]=="person"

//                ClTagset **child == new *child[1] (new ClTagset Array Pointer der Länge 1)

//            child[0] == NULL; (ClTagset Objekt an der Stelle des ClTagset-Arrays "child[]" an der Stelle child[0] NULL setzen)
//        */

////child=tagset->getChild(0);
//        /*
//        ClTagset *child == *tagset->getChild(0)
//            child->anzahlTags==1
//            child->*tagNamen[1]
//                child->tagNamen[0]=="person"
//            child->*child[1]
//                child->child[0]==NULL
//        */

////child->addTagset(2,0,elemente3);
//        /* ==> child->child[0]

//          child->child[0] = new ClTagset(2, element3)

//            anzahlTags == 2

//               **tagNamen == *tagNamen[2]

//                tagNamen[0] == new char[64]
//                tagNamen[0] =  element3[0] == "vorname"

//            tagNamen[0] == "vorname"

//                tagNamen[1] == new char[64]
//                tagNamen[1] =  element3[1] == "famname"

//            tagNamen[1] == "famname"

//                ClTagset **child == new *child[2]

//             child[0] == NULL
//             child[1] == NULL
//        */


