#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

#define MAX_LEN 10

typedef struct sP
{
    char sid1[MAX_LEN] ;
    char sid2[MAX_LEN] ;
    float wgt ;
} studentPair ;

typedef struct aLN
{
    string sid2 ;
    float weight ;
    struct aLN *next ;
} adjListNode ;

typedef struct aL
{
    string sid1 ;
    adjListNode *head ;
    int inf ;
    vector<string> infList ;
} adjList ;


class DM   // Data manage and In/Output
{

    vector< studentPair > orinList;
    string fname ;

    void ReadFileName()
    {
        fname.clear() ;
        cin >> fname ;
    } // ReadFileName()

public:

    string GetFileName()
    {
        return fname ;
    } // GetFileName()

    bool ReadBin()
    {

        fstream binFile ;
        studentPair onePr ;
        int stNo = 0 ;

        binFile.open( ("pairs" + fname + ".bin" ).c_str(), fstream::in | fstream::binary ) ;

        if ( binFile.is_open() )
        {

            binFile.seekg(0,binFile.end) ; // Goto the end of file
            stNo = binFile.tellg() / sizeof(onePr) ;
            binFile.seekg(0,binFile.beg) ; // Goto the begin

            for ( int i = 0 ; i<stNo ; i++ )
            {
                binFile.read( (char*)&onePr, sizeof(onePr) ) ;
                orinList.push_back(onePr) ;
                // cout << "[" << i+1 << "]" << '\t' << onePr.sid1 << '\t' << onePr.sid2 << '\t' << onePr.wgt << endl ; // total data
            } // for
            // cout << stNo << endl ;
        } // if
        else
        {
            return false ;
        }
        binFile.close() ;
        return true ;

    } // ReadBin()

    bool ReadFile()
    {

        orinList.clear() ;

        /*---------- deal with File ----------*/
        do
        {
            cout << "Input a file number (401, 402, ...[0]Quit): " ;
            ReadFileName() ;

            if ( fname == "0" )
            {
                return false ;
            } // Quit to open file

            cout << endl ;

            if ( ReadBin() )
            {
                break ;
            }
            else
            {
                cout << "Error:Open file fail" << endl << endl ;
            } // if Error

        }
        while ( true ) ;

        return true ;

    } // ReadFile()

    studentPair GetData( int pos )
    {
        return orinList.at(pos) ;
    } // GetData()

    int GetSize()
    {
        return orinList.size() ;
    } // GetSize()

    void Write( vector<adjList> adjL, int size, int totalNode, string fileType )
    {

        ofstream fOut( ("pairs" + fname + "." + fileType ).c_str() ) ;

        fOut << "<<< There are " << size << " IDs in total. >>>" << endl ;


        for ( int i = 0 ; i < size ; i ++ )
        {

            /*---------- adj ----------*/
            if ( fileType == "adj" )
            {

                fOut << "[" << right << setw(3) << i+1 << "] "
                     << adjL.at(i).sid1 << ": " << endl ;

                adjListNode *temp = adjL.at(i).head ;
                int count = 0 ;

                while( temp != NULL )
                {

                    count++ ;
                    fOut << '\t' << "(" << right << setw(2) << count << ") "
                         << temp->sid2 << ",  "
                         << setw(4) << temp->weight ;

                    if ( count%10 == 0  )
                        fOut << endl ;

                    temp = temp->next ;

                } // while

                fOut << endl ;
            } // if
            /*---------- cnt ----------*/
            else if ( fileType == "cnt" )
            {

                fOut << "[" << right << setw(3) << i+1 << "] "
                     << adjL.at(i).sid1 << "(" << adjL.at(i).inf << ")" << ": " << endl ;

                for ( int j = 0 ; j < adjL[i].infList.size() ; j++ )
                {

                    fOut << '\t' << "(" << right << setw(2) << j+1 << ") "
                         << adjL[i].infList[j] ;

                    if ( (j+1)%10 == 0  )
                        fOut << endl ;

                } // for

                fOut << endl ;

            } // else if

            /*---------- inf ----------*/
            else if(fileType == "inf")
            {
                fOut << "[" << right << setw(3) << i+1 << "] "
                     << adjL.at(i).sid1 << "(" << adjL.at(i).inf << ")" << ": " << endl ;

                for ( int j = 0 ; j < adjL[i].infList.size() ; j++ )
                {

                    fOut << '\t' << "(" << right << setw(2) << j+1 << ") "
                         << adjL[i].infList[j] ;

                    if ( (j+1)%10 == 0  )
                        fOut << endl ;

                } // for

                fOut << endl ;
            }
        } // for



        if ( fileType == "adj" )
            fOut << "<<< There are " << totalNode << " nodes in total. >>>" << endl ;

        fOut.close() ;

    } // Write()

}; // Class FileIO

class DirectoryGraph
{

    vector<string> allIDs ;

    vector<adjList> adjL ;

    int search( string id )
    {

        for( int i=0 ; i<adjL.size() ; i++  )
        {
            if ( !id.compare( adjL.at(i).sid1 ) )
            {
                return i ;
            } // if
        } // for

        return -1 ;

    } // IsIDExist()

    int InsertPos( string id )
    {
        int pos = 0 ;
        while ( adjL.at(pos).sid1.compare( id ) < 0 ) pos++ ;

        return pos ;
    } // InsertPos

    adjListNode* CreatAdjNode( string id, float weight )
    {

        adjListNode *newNode = new adjListNode ;
        newNode->sid2 = id ;
        newNode->weight = weight ;
        newNode->next = NULL ;

        return newNode ;

    } // CreatAdjNode()

    void insertAdjNode( adjList &adj, adjListNode *newAdjNode )
    {

        adjListNode *cur = adj.head ;
        adjListNode *prev = cur ;

        while ( cur != NULL )
        {

            if( newAdjNode->weight > cur->weight ) break ;
            prev = cur ;
            cur = cur->next ;

        } // while

        // if is the first data
        if ( cur == adj.head )
        {
            // cout << prev->sid2 << endl ; // debug line
            newAdjNode->next = prev ;
            adj.head = newAdjNode ;
        } // if
        else
        {
            newAdjNode->next = prev->next ;
            prev->next = newAdjNode ;
        } // else


    } // insertAdjNode()

    adjList CreatAdj( string id )
    {

        adjList newNode ;
        newNode.sid1 = id ;
        newNode.head = NULL ;
        newNode.inf = 0 ;

        return newNode ;

    } // CreatAdj()

    vector<string> iterativeBFS( adjList adj )
    {

        vector<string> visited ;
        queue<string> q ;
        q.push( adj.sid1 ) ;
        visited.push_back( adj.sid1 ) ;

        while( !q.empty() )
        {

            string tempId = q.front() ;
            q.pop() ;
            adjListNode *cur = adjL.at( this->search(tempId) ).head ;
            adjListNode *prev = cur;
            while( cur != NULL )
            {

                if ( find( visited.begin(), visited.end(), cur->sid2 ) == visited.end() )
                {
                    visited.push_back( cur->sid2 ) ;
                    q.push( cur->sid2 ) ;

                } // if

                cur = cur->next ;
            } // while

        } // while

        visited.erase( visited.begin() ) ;

        //Sort2(visited);
        sort(visited.begin(), visited.end(), less<string>());

        return visited ;

    } // iterativeBFS()

    vector<string> iterativeDFS( adjList adj, float n)
    {

        vector<string> visited ;

        stack<string> s ;
        s.push( adj.sid1 ) ;
        //cout << adj.sid1 << endl;
        visited.push_back( adj.sid1 ) ;

        while( !s.empty() )
        {

            string tempId = s.top() ;
            s.pop();
            adjListNode *cur = adjL.at( this->search(tempId) ).head ;

            while( cur != NULL)
            {

                if (find(visited.begin(), visited.end(), cur->sid2 ) == visited.end())
                {
                    if(cur->weight >= n)
                    {
                        //cout << cur->sid2 << endl;
                        s.push( cur->sid2 ) ;
                        visited.push_back( cur->sid2 ) ;
                    }

                } // if
                cur = cur->next ;
            } // while

        } // while

        visited.erase( visited.begin() ) ;

        sort(visited.begin(), visited.end(), less<string>());

        return visited ;

    } // iterativeBFS()

public:

    void BFSBuild()
    {

        for( int i = 0 ; i<adjL.size() ; i++ )
        {

            adjL.at(i).infList = iterativeBFS( adjL.at(i) ) ;
            adjL.at(i).inf = adjL.at(i).infList.size() ;
            /*
                        cout << adjL.at(i).sid1 ; // debug line

                        for ( int j = 0 ; j<adjL.at(i).infList.size() ; j++ ) {
                            cout << "\t" << adjL.at(i).infList.at(j) ; // debug line
                        } // for

                        cout << endl ;
            */
        } // for

    } // BFSBuild()

    void insert( studentPair onePair )
    {

        /*------ Record IDs ------*/

        // allIDs.push_back( onePair.sid2 ) ;

        /*------ Check id is Exist -------*/

        int pos = search( onePair.sid1 ) ;

        // ID Exist
        if ( pos != -1 )
        {

            if ( adjL.at(pos).head != NULL )
                insertAdjNode( adjL.at(pos), CreatAdjNode( onePair.sid2, onePair.wgt ) ) ;

            // Print() ;

        } // if
        // ID is Not Exist
        else
        {
            /*
            adjL.reserve(100 ) ;
            adjL.insert( adjL.begin()+InsertPos(onePair.sid1), CreatAdj(onePair.sid1) ) ;
            */
            adjL.push_back( CreatAdj(onePair.sid1) ) ;
            pos = adjL.size()-1 ;

            if ( adjL.at(pos).head == NULL )
                adjL.at(pos).head = CreatAdjNode( onePair.sid2, onePair.wgt ) ;

        } // else


    } // insert()

    void DFSBuild()
    {
        float num = 0.0;
        while(true)
        {
            cout << endl << "Input a real number in [0,1]:";
            cin >> num;
            if(num > 0 && num <= 1) break;
            else
                cout << endl <<"### It is NOT in [0,1] ###" << endl;
        }

        for( int i = 0 ; i<adjL.size() ; i++ )
        {

            adjL.at(i).infList = iterativeDFS( adjL.at(i), num ) ;
            adjL.at(i).inf = adjL.at(i).infList.size() ;

//            cout << adjL.at(i).sid1 << ":" << endl; // debug line
//
//            for ( int j = 0 ; j<adjL.at(i).infList.size() ; j++ )
//            {
//                cout  << adjL.at(i).infList.at(j) << endl; // debug line
//            } // for
//
//            cout << endl ;

        } // for

    } // BFSBuild()

    void Print()
    {

        for( int i=0 ; i<adjL.size() ; i++ )
        {

            cout << adjL.at(i).sid1 ;

            adjListNode *temp = adjL.at(i).head ;
            while ( temp != NULL )
            {
                cout<< " <--[" << temp->weight << "]-- " << temp->sid2 ;
                temp = temp->next ;
            } // while

            cout << endl << endl ;

        } // for

    } // Print()

    void ChecksIDs()
    {

        for ( int i = 0 ; i<adjL.size() ; i++ )
        {

            adjListNode *temp = adjL.at(i).head ;

            if ( !count( allIDs.begin(), allIDs.end(), adjL.at(i).sid1 ) )
                allIDs.push_back(adjL.at(i).sid1) ;

            while ( temp != NULL )
            {

                if ( !count( allIDs.begin(), allIDs.end(), temp->sid2 ) )
                    allIDs.push_back(temp->sid2) ;

                temp = temp->next ;
            } // while

        } // for

        // cout << "[" << allIDs.size() << "]" << endl ; // debug line

        if ( allIDs.size() != adjL.size() )
        {

            for ( int i = 0 ; i<allIDs.size() ; i++ )
            {

                if ( this->search( allIDs.at(i) ) == -1 )
                    adjL.push_back( CreatAdj( allIDs.at(i) ) ) ;
                /*
                for ( int j = 0 ; j<adjL.size() ; j++ ) {

                    if ( adjL.at(j).sid1.compare( allIDs.at(i) ) == 0 ) break ;
                    if ( j == adjL.size()-1 ) adjL.push_back( CreatAdj( allIDs.at(i) ) ) ;

                } // for
                */

            } // for

        } // if


    } // ChecksIDs()

    void Sort( int mission )
    {

        for ( int i = 0 ; i<adjL.size()-1 ; i++ )
        {
            for ( int n = i+1 ; n<adjL.size() ; n++ )
            {

                if ( mission == 1 )
                {
                    if ( adjL.at(i).sid1.compare( adjL.at(n).sid1 ) > 0 )
                    {
                        adjList temp = adjL.at(n) ;
                        adjL.at(n) = adjL.at(i) ;
                        adjL.at(i) = temp ;

                    } // if
                } // if

                else if ( mission == 2 )
                {

                    if ( adjL.at(i).inf < adjL.at(n).inf )
                    {
                        adjList temp = adjL.at(n) ;
                        adjL.at(n) = adjL.at(i) ;
                        adjL.at(i) = temp ;

                    } // if
                    else if ( adjL.at(i).inf == adjL.at(n).inf )
                    {
                        if ( adjL.at(i).sid1.compare( adjL.at(n).sid1 ) > 0 )
                        {
                            adjList temp = adjL.at(n) ;
                            adjL.at(n) = adjL.at(i) ;
                            adjL.at(i) = temp ;
                        } // if
                    } // else if

                } // else if

            } // for
        } // for

    } // Sort()

    vector<adjList> GetAdjList()
    {
        return adjL ;
    } // GetAdjList()

    int GetSize()
    {
        return adjL.size() ;
    } // GetSize()

    void Clear()
    {

        adjL.clear() ;
        allIDs.clear() ;

    } // Clear()

    void BFSsearch( string startID, string targetID, double &sum ) {

        int startIDPos = search( startID ) ;

        if ( startIDPos == -1 || search( targetID ) == -1 ) cout << "ERROE:There is no ID in adjList!" << endl << endl ;
        else {

            vector<string> visited ;
            queue<string> q ;
            q.push( startID ) ;
            visited.push_back( startID ) ;

            while( !q.empty() )
            {

                string tempId = q.front() ;
                q.pop() ;
                adjListNode *cur = adjL.at( this->search(tempId) ).head ;


                while( cur != NULL )
                {

                    if ( find( visited.begin(), visited.end(), cur->sid2 ) == visited.end() )
                    {
                        sum += cur->weight ;

                        if ( cur->sid2 == targetID )
                        {
                            cout << "successful" << endl ;
                            return ;
                        }
                        visited.push_back( cur->sid2 ) ;
                        q.push( cur->sid2 ) ;

                    } // if

                    cur = cur->next ;
                } // while

            } // while

        } // else

        cout << "They're disconnected!" << endl ;

    } // BFSsearch()

    void DFSsearch( string startID, string targetID, double &sum ) {

        int startIDPos = search( startID ) ;

        if ( startIDPos == -1 || search( targetID ) == -1 ) cout << "ERROE:There is no ID in adjList!" << endl << endl ;
        else {

            vector<string> visited ;
            stack<string> s ;
            s.push( startID ) ;
            visited.push_back( startID ) ;

            while( !s.empty() )
            {

                string tempId = s.top() ;
                s.pop() ;
                adjListNode *cur = adjL.at( this->search(tempId) ).head ;

                while( cur != NULL )
                {

                    if ( find( visited.begin(), visited.end(), cur->sid2 ) == visited.end() )
                    {
                        sum += cur->weight ;

                        if ( cur->sid2 == targetID )
                        {
                            cout << "successful" << endl ;
                            return ;
                        }
                        visited.push_back( cur->sid2 ) ;
                        s.push( cur->sid2 ) ;

                    } // if

                    cur = cur->next ;
                } // while

            } // while

            visited.erase( visited.begin() ) ;

        } // else

        cout << "They're disconnected!" << endl ;

    } // DFSsearch()

}; // class DirectoryGraph

class Mission
{

    DM dataList ;
    DirectoryGraph List ;
    DirectoryGraph TempList;

public:
    double start = 0.0;
    double ending = 0.0;
    void DisplayMission()
    {

        cout << endl << "**********     HASH TABLE   **********" ;
        cout << endl << "                                      " ;
        cout << endl << "* 0. QUIT                            *" ;
        cout << endl << "* 1. Build adjacency lists           *" ;
        cout << endl << "* 2. Compute infList value           *" ;
        cout << endl << "* 3. Estimate influence values       *" ;
        cout << endl << "* 4. Compare DFS and BFS Cost        *" ;
        cout << endl << "                                      " ;
        cout << endl << "**************************************" ;
    } // End displayMission

    void One( )
    {
        if( dataList.ReadFile() )
        {

            List.Clear() ;
            TempList.Clear();

            for ( int i = 0 ; i<dataList.GetSize() ; i++ )
            {
                List.insert( dataList.GetData(i) ) ;
            } // for
            List.ChecksIDs() ;
            List.Sort(1) ;
            // List.Print() ;
            TempList = List;
            cout << "<<< There are " << List.GetSize() << " IDs in total. >>>" << endl << endl ;
            cout << "<<< There are " << dataList.GetSize() << " nodes in total. >>>" << endl ;

            dataList.Write( List.GetAdjList(), List.GetSize(), dataList.GetSize(), "adj" ) ;

        } // if
    } // One()

    void Two( )
    {
        if ( List.GetSize() != 0 )
        {
            start = clock();
            List.BFSBuild() ;
            ending = clock();
            List.Sort(2) ;
            cout << "time: " << (ending - start) / CLOCKS_PER_SEC << endl;
            cout << "<<< There are " << List.GetSize() << " IDs in total. >>>" << endl << endl ;

            dataList.Write( List.GetAdjList(), List.GetSize(), dataList.GetSize(), "cnt" ) ;

        } // if
        else
        {
            cout << "### There is no graph and choose 1 first. ###" << endl ;
        } // else

    } // Two()

    void Three( )
    {
        //List = TempList;
        if ( TempList.GetSize() != 0 )
        {

            TempList.DFSBuild() ;
            TempList.Sort(2);

            cout << "<<< There are " << TempList.GetSize() << " IDs in total. >>>" << endl << endl ;

            dataList.Write( TempList.GetAdjList(), TempList.GetSize(), dataList.GetSize(), "inf" ) ;

        } // if
        else
        {
            cout << "### There is no graph and choose 2 first. ###" << endl ;
        } // else


    } // Three()

    void Four( )
    {
        //List = TempList;
        if ( TempList.GetSize() != 0 )
        {

            string startingID, targetID ;
            double BFSWeight = 0.0, DFSWeight = 0.0 ;

            cout << "Enter a start ID: " ;
            cin >> startingID ;

            cout << "Enter a target ID: " ;
            cin >> targetID ;

            cout << endl << endl ;

            start = clock();
            List.BFSsearch( startingID, targetID, BFSWeight ) ;
            ending = clock();
            cout << "BFS search cost time: " << (ending - start) / CLOCKS_PER_SEC << " s" << endl ;
            cout << "Sum of path's weight: " << BFSWeight << " weight" << endl << endl ;

            start = clock();
            List.DFSsearch( startingID, targetID, DFSWeight ) ;
            ending = clock();
            cout << "DFS search cost time: " << (ending - start) / CLOCKS_PER_SEC << " s" << endl ;
            cout << "Sum of path's weight: " << DFSWeight << " weight" << endl ;

        } // if
        else
        {
            cout << "### There is no graph and choose 1 first. ###" << endl ;
        } // else


    } // Four()

}; // class Mission


int main()
{

    Mission mission ;
    int command ;

    do
    {
        mission.DisplayMission() ;
        cout << endl << "Input a choice(0,1,2,3,4): " ;
        cin >> command ;
        cout << endl ;

        switch ( command )
        {

        case 0:
            break ;
        case 1:
            mission.One() ;
            break ;

        case 2:
            mission.Two() ;
            break ;

        case 3:
            mission.Three() ;
            break ;

        case 4:
            mission.Four() ;
            break ;

        default :
            cout << "Command dose not exist!" << endl ;
        } // switch()

        cout << endl ;

    }
    while ( command != 0 ) ;

    return 0;

} // main()





