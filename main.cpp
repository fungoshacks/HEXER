#include "ProcessMonitor.h"
#include "MutationFactory.h"
#include "Mutation.h"
#include "CrashAnalyser.h"
#include "time.h"
#include <thread>
#include "windows.h"
#include <vector>
#include <iostream>
#include <fstream>

void usage();
void logo();
void work(string, string, int, int, int);
void check_crash(string, string);
vector<vector<char>> *buildCorpuses(string);

vector<vector<char>> *_corpuses;

int 
main( int argc, char *argv[] )
{

    if ( argc < 6 )
        usage();

    string path_exe = argv[1];
    string path_corpuses = argv[2];
    int num_threads = atoi(argv[3]);
    int ttl = atoi(argv[4]);
    int aggr = atoi(argv[5]);
    std::thread *threads = new std::thread[num_threads];
    logo();

    _corpuses = buildCorpuses(path_corpuses);

    for (unsigned int i = 0; i < num_threads; i++) {
	threads[i] = std::thread(work,path_exe, path_corpuses, i * 1337, ttl, aggr);
    }

    for (unsigned int i = 0; i < num_threads; i++) {
	threads[i].join();
    }

    delete threads;
    
    return 0;
}

void
work(string path_exe, string path_corpuses, int seed, int ttl, int aggr)
{

   Mutation *mut_tmp;
   ProcessMonitor procMon(path_exe, ttl);
   CrashAnalyser crashAnalyser(&procMon);
   MutationFactory mut_factory(_corpuses, aggr);
   bool crashed = false;

   srand(time(NULL) + seed);
   while ( true ) {

	try{
	       mut_tmp = mut_factory.new_mutation();
	       if ( procMon.doesCrash(mut_tmp->getMutationPath()) ) {

		       crashAnalyser.checkcrash(mut_tmp->getMutationPath());
			
	       } else {
		   remove(mut_tmp->getMutationPath().c_str());
	       }
	}catch(...){
	    printf("[--] Worker error");	
	}

       delete mut_tmp;

   }

}

vector<vector<char>> *
buildCorpuses(string corpus_dir)
{

    vector<vector<char>> *corpuses = new vector<vector<char>>();
    vector<string>  corpus_paths;
    HANDLE hFind;
    WIN32_FIND_DATA data; 
    int cntr = 0;
    string tmp_path;

    /* Get a list of all corps paths */
    hFind = FindFirstFile(corpus_dir.c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
           if ( cntr < 2 ) {
               cntr++;
               continue;
            }

	    
	    tmp_path = string(corpus_dir).substr(0, strlen(corpus_dir.c_str()) -1 ).append(data.cFileName);

	    ifstream file(tmp_path, std::ios::binary | std::ios::ate);
	    streamsize size = file.tellg();
	    file.seekg(0, std::ios::beg);
	    vector<char> corpus_buffer(size);

    	    if ( file.read(corpus_buffer.data(), size )) {

		corpuses->push_back(corpus_buffer);

	    }

        } while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }



    return corpuses;

}

void
logo()
{

    printf("                                    /sdN/                                                 \n");
    printf("                                 :yNMmyyms/                                               \n");
    printf("                               omMNhhyyyyhN.                                              \n");
    printf("                             `ohyyydyyyyyyhh`                                             \n");
    printf("                            oyyyhdmNyyyyyyymd`                                            \n");
    printf("                           yMhsoyysmyyyyyyyyNm.                                           \n");
    printf("                           ``     :NyyyyhyyyyNh                                           \n");
    printf("                                  :MhyyyyyyyyhM:                                          \n");
    printf("                                  :NyyyyyyyyyydN.                                         \n");
    printf("                                  +dyyyyyyyyyyydy                                         \n");
    printf("                                  yhyyyyyyhyyyyyN-                                        \n");
    printf("                                  mdyyyyyyyyyyyyNh                                        \n");
    printf("                                 :MyyyyyyyyyyyyyhM.                                       \n");
    printf("                                 hmyyyyyyyyyyyyyyMs                                       \n");
    printf("                                :Nyyyydmhyyyyyyyydd                                       \n");
    printf("                                ddyyyddyNhyyyyyyyyNsooooo:                                \n");
    printf("                      ``-/osyyshNyyyyN/.-hyyyyyyyydMdyyhdmmho:`                           \n");
    printf("                  -shdddhhyyyyhNhyyyym-.:ddyyyyyyyyNNyhhyyyyyhmh+.                        \n");
    printf("              .+hmhyyyyyyyyyyyhNyyyyydm/smyyyyyyyyymMhyyyyyyyyyyhmd/`                     \n");
    printf("           `/dmhyyyyyyyyyyyyyyNhyyyyyyhMmyyyyyyyhNNmdyyyyyyyyyyyyyhdmd/.                  \n");
    printf("          /dmhyyyyyyyhyyyyyyydNmmmdhhhyyyhhdmddhhhyyyyyyyyyyyyyyyyydhhNs.                 \n");
    printf("            `:syyyNMNmdhhhyyyyyyyyhhhhhhhhhyyyyyyyyyyyyyyyyhhdmmNdh+-.                    \n");
    printf("                   `:/oNmmNmdhhhhyyyyyyyyyhhhhddddmmmmmmNNNNyo+-`                         \n");
    printf("                      .doy.:+oMMMdyhhyyhyyssso+///hNy--.hyso                              \n");
    printf("                      /yym-mMhyddNm+:.........-sNhs++o/.m/+m-                             \n");
    printf("                      oshN+NNooNMmhhm+.......omyoydhNM++h//+d`                            \n");
    printf("                     `d+sNs.-/+shh/...../d/./s/dMMhsNN-ho///oh`                           \n");
    printf("                     `y//dN-............-Nm-...:/+//+:-///////.                           \n");
    printf("                     `///smh-........./y-:Nm-.........yo//////+h                          \n");
    printf("                      .h/ysh/.........mm-.:Nm........-m//////oo:y                         \n");
    printf("                     `hy/////:.....-:+MNNhysNo.......hs///////y/                          \n");
    printf("                     `y/////////+s/ohyo+///////dy/-.+d/////o//d:                          \n");
    printf("                    `ho////h+///hs/+yhhdddmddmhyoyh+///////ds/sy`                         \n");
    printf("                    ys/od//m///od/sMh/--.:-  `/mN+/s+/////odo//mo                         \n");
    printf("                   -y///m//d+//m+/sm/+++++++++yhmo/soho///oo///hd`                        \n");
    printf("                   s--d+y/////s///sssssoosoooooo/////yh////////y:                         \n");
    printf("                      +h//////sd//////////ds//////////ds//////+d`                         \n");
    printf("                     s:moso////yd////////oh/////o////+m+//+hhsh+                          \n");
    printf("                     `yho:hs////sd+//+///++/////m////yy//sho-//                           \n");
    printf("                          `ys////yy//m+//do/////do///o//hh+:.                             \n");
    printf("                            ys///+m//ho//sh/////do////o/::.                               \n");
    printf("                             y////o//o+//+h//+//s///+s.                                   \n");
    printf("                               yy+/////////////y///o+.                                    \n");
    printf("                                :dsyho//////+++hoos.                                      \n");
    printf("                                  ` `/+/yso/+:/`                                          \n");

    printf("\t\t\t _   _  _______   __ ___________\n");
    printf("\t\t\t| | | ||  ___\\ \\ / /|  ___| ___ \n");
    printf("\t\t\t| |_| || |__  \\ V / | |__ | |_/ /\n");
    printf("\t\t\t|  _  ||  __| /   \\ |  __||    /\n");
    printf("\t\t\t| | | || |___/ /^\\ \\| |___| |\\ \\ \n");
    printf("\t\t\t\\_| |_/\\____/\\/   \\/\\____/\\_| \\_|\n");
    printf("v2223\n");

}

void
usage()
{
    printf("Usage: Hexer <path executable> <path corpus dir> <num_threads> <ttl> <aggression>");
    exit(0);
}
