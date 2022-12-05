#pragma once
#include <iostream>
#include<fstream>
#include<sstream>
using namespace std;
template <typename I, typename S, typename F>
class AD;
template <typename I, typename S, typename F>
class MMD;
template <typename I, typename S >
class AMD;
template <typename I>
class Tracks;
class ADP;
class Albums;
template <typename I, typename S, typename F>
void storeMMDHead(MMD<I, S, F>*);
template <typename I, typename S, typename F>
MMD<I, S, F>* getMMDHead();
template <typename I, typename S >
void storeAMDHead(AMD<I, S >*);
template <typename I, typename S >
AMD<I, S>* getAMDHead();
template <typename I, typename S, typename F>
void storeADHead(AD<I, S, F>*);
template <typename I, typename S, typename F>
AD<I, S, F>* getADHead();
template <typename I>
void linkTracksWithMMD(Tracks<I>*, int);


void linkAlbumsWithAD(Albums*, int);

//#############################################################################
//#############################################################################
//                                  MMD
//#############################################################################
//#############################################################################

//Music Metadata DataBase (A doubly linked list)
template <typename I, typename S, typename F>
class MMD
{
public:
	//data members
	I mbid;
	S song_name;
	S writer;
	F length;
	AD<I, S, F>* album;

	//connections
	MMD<I, S, F>* next;
	MMD<I, S, F>* previous;

	//default constructor
	MMD()
	{
		next = NULL;
		previous = NULL;
	}
};
template <typename I, typename S, typename F>
MMD<I, S, F>* Create_MMD(std::string);

template <typename I, typename S, typename F>
class MMD_List
{
public:
	MMD<I, S, F>* Head;
	MMD_List()
	{
		Head = NULL;
	}

	MMD<I, S, F>* getHead()
	{
		return Head;
	}

	MMD<I, S, F>* createMMDNode(int mbid, std::string song_name, std::string writer, double length)
	{
		MMD<I, S, F>* new_MMD_node = new MMD<I, S, F>;
		new_MMD_node->mbid = mbid;
		new_MMD_node->song_name = song_name;
		new_MMD_node->writer = writer;
		new_MMD_node->length = length;
		return new_MMD_node;
	}

	bool checkMMDEmpty()
	{
		if (Head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	MMD<I, S, F>* addMMDNode(int mbid, std::string song_name, std::string writer, double length)
	{
		MMD <I, S, F>* new_MMD_Node = new MMD<I, S, F>;
		new_MMD_Node = createMMDNode(mbid, song_name, writer, length);
		if (checkMMDEmpty() == 1)
		{
			Head = new_MMD_Node;
		}
		else
		{
			MMD<I, S, F>* temp;
			temp = Head;

			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = new_MMD_Node;
			new_MMD_Node->previous = temp;
		}
		return Head;
	}

	void displayMMDList()
	{
		MMD<I, S, F>* temp;
		temp = Head;
		while (temp->next != NULL)
		{
			std::cout << "********************************" << std::endl;
			std::cout << "MBID : " << temp->mbid << std::endl;
			std::cout << "Song Name : " << temp->song_name << std::endl;;
			std::cout << "Writer : " << temp->writer << std::endl;
			std::cout << "Length : " << temp->length << std::endl;
			temp = temp->next;
		}
		std::cout << "********************************" << std::endl;
		std::cout << "MBID : " << temp->mbid << std::endl;
		std::cout << "Song Name : " << temp->song_name << std::endl;;
		std::cout << "Writer : " << temp->writer << std::endl;
		std::cout << "Length : " << temp->length << std::endl;
	}


};





//
////#############################################################################
////#############################################################################
////                                  AMD
////#############################################################################
////#############################################################################
//
////Author Metadata DataBase (A circular linked list)
template <typename I, typename S >
class AMD
{
public:
	//data members
	I aid;
	S name_of_author;
	S  name_of_band;
	S gender_of_author;
	I date_of_birth;
	I date_of_release;
	S genre;
	AD<I, S, float>* albums;
	//ADP* adp;


	//connections
	AMD<I, S>* next;
};

template <typename I, typename S >
AMD<I, S>* amd_head;

template <typename I, typename S >
class AMD_List
{
public:
	AMD<I, S>* Head;
	AMD_List()
	{
		Head = NULL;
	}

	AMD<I, S >* createAMDNode(int aid, std::string name_of_author, std::string name_of_band, std::string gender_of_author, long int date_of_birth, long int date_of_release, std::string genre)
	{
		AMD< I, S>* new_AMD_node;
		new_AMD_node = new AMD<I, S>;
		new_AMD_node->aid = aid;
		new_AMD_node->name_of_author = name_of_author;
		new_AMD_node->name_of_band = name_of_band;
		new_AMD_node->gender_of_author = gender_of_author;
		new_AMD_node->date_of_birth = date_of_birth;
		new_AMD_node->date_of_release = date_of_release;
		new_AMD_node->genre = genre;
		return new_AMD_node;
	}

	bool checkAMDEmpty()
	{
		if (Head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	AMD< I, S>* addAMDNode(int aid, std::string name_of_author, std::string name_of_band, std::string gender_of_author, long int date_of_birth, long int date_of_release, std::string genre)
	{
		AMD<I, S>* new_AMD_Node = createAMDNode(aid, name_of_author, name_of_band, gender_of_author, date_of_birth, date_of_release, genre);
		if (checkAMDEmpty() == 1)
		{
			Head = new_AMD_Node;
			new_AMD_Node->next = new_AMD_Node;
		}
		else
		{
			AMD< I, S>* temp;
			temp = Head;
			while (temp->next != Head)
			{
				temp = temp->next;
			}
			temp->next = new_AMD_Node;
			new_AMD_Node->next = Head;
		}
		return Head;

	}

	void displayAMDList()
	{
		AMD<I, S>* temp;
		temp = Head;
		while (temp->next != Head)
		{
			std::cout << "********************************" << std::endl;
			std::cout << "AID : " << temp->aid << std::endl;
			std::cout << "Author Name : " << temp->name_of_author << std::endl;;
			std::cout << "Name of Band : " << temp->name_of_band << std::endl;
			std::cout << "Gender of Author : " << temp->gender_of_author << std::endl;
			std::cout << "Date of Birth : " << temp->date_of_birth << std::endl;
			std::cout << "Date of Release : " << temp->date_of_release << std::endl;
			std::cout << "Genre : " << temp->genre << std::endl;
			temp = temp->next;
		}
		std::cout << "********************************" << std::endl;
		std::cout << "AID : " << temp->aid << std::endl;
		std::cout << "Author Name : " << temp->name_of_author << std::endl;;
		std::cout << "Name of Band : " << temp->name_of_band << std::endl;
		std::cout << "Gender of Author : " << temp->gender_of_author << std::endl;
		std::cout << "Date of Birth : " << temp->date_of_birth << std::endl;
		std::cout << "Date of Release : " << temp->date_of_release << std::endl;
		std::cout << "Genre : " << temp->genre << std::endl;
	}
};
//
//
//
//
//
//
////#############################################################################
////#############################################################################
////                                  TRACKS
////#############################################################################
////#############################################################################


//Tracks (A singly linked list)
template<typename  I>
class Tracks
{
public:
	//data members
	I trackNumber;
	I track_mbid;
	MMD<I, std::string, float>* trackRef;

	//connections
	Tracks<I>* next;
};


template<typename  I>
class Tracks_List
{
public:
	Tracks<I>* Head;
	Tracks_List()
	{
		Head = NULL;
	}

	Tracks<I>* createTracksNode(int track_number, int track_mbid)
	{
		Tracks<I>* new_Track_node;
		new_Track_node = new Tracks<I>;
		new_Track_node->trackNumber = track_number;
		linkTracksWithMMD(new_Track_node, track_mbid);

		return new_Track_node;
	}

	bool checkTracksEmpty()
	{
		if (Head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Tracks<I>* addFirstNode(int track_number, int track_mbid)
	{
		Tracks<I>* new_Track_Node = createTracksNode(track_number, track_mbid);
		if (checkTracksEmpty() == 1)
		{
			Head = new_Track_Node;
			new_Track_Node->next = NULL;

		}
		return Head;
	}


	void displayTrackList()
	{
		Tracks<I>* temp;
		temp = Head;
		std::cout << "######################################" << std::endl;
		std::cout << "Displaying Track List" << std::endl;
		std::cout << "######################################" << std::endl;
		while (temp != NULL)
		{
			std::cout << "Track NUmber : " << temp->trackNumber;
		}
	}


};
template <typename I>
void linkTracksWithMMD(Tracks<I>* new_Track_node, int track_mbid)
{
	MMD<I, std::string, float>* temp1;
	temp1 = temp_MMD_head< I, std::string, float>;
	while (temp1->mbid != track_mbid)
	{
		temp1 = temp1->next;
	}
	new_Track_node->trackRef = temp1;
}

template <typename I>
void addMoreNodes(Tracks<I>* Head, int track_number, int track_mbid)
{
	Tracks<I>* new_Track_Node = new Tracks<I>;
	new_Track_Node->trackNumber = track_number;
	linkTracksWithMMD(new_Track_Node, track_mbid);

	Tracks<I>* temp;
	temp = Head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new_Track_Node;
	new_Track_Node->next = NULL;



}

//
//
//
//
//
//
//
////#############################################################################
////#############################################################################
////                                  AD (ALBUM DATABASE)
////#############################################################################
////#############################################################################
//


////Album DataBase (A circular linked list)
template<typename I, typename S, typename F>
class AD
{
public:
	//data members
	I abid;
	S album_name;
	I aid;
	S publisher;
	I number_of_tracks;
	F total_duration;
	//int track_number;
	I track_mbid;
	AMD<I, S>* author;
	Tracks<I>* tracks;
	//ADP* adp;

	//connections
	AD<I, S, F>* next;
};

template <typename I, typename S, typename F>
class AD_List
{
public:
	AD<I, S, F>* Head;
	AD_List()
	{
		Head = NULL;
	}

	AD<I, S, F >* getHeadAddress()
	{
		return Head;
	}

	AD<I, S, F>* createADNode(int abid, std::string album_name, int aid, std::string publisher, int number_of_tracks, double total_duration, int track_number, int track_mbid)
	{
		Tracks_List<I> T1;
		//storeTracksHead(T1.Head);
		AD<I, S, F>* new_AD_node;
		new_AD_node = new AD<I, S, F>;
		new_AD_node->abid = abid;
		new_AD_node->album_name = album_name;
		new_AD_node->aid = aid;
		new_AD_node->publisher = publisher;
		new_AD_node->number_of_tracks = number_of_tracks;
		new_AD_node->total_duration = total_duration;
		new_AD_node->tracks = T1.addFirstNode(track_number, track_mbid);
		//new_AD_node->track_number = track_number;
		new_AD_node->track_mbid = track_mbid;
		return new_AD_node;
	}

	bool checkADEmpty()
	{
		if (Head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	AD<I, S, F>* addADNode(int abid, std::string album_name, int aid, std::string publisher, int number_of_tracks, double total_duration, int track_number, int track_mbid)
	{
		AD<I, S, F>* new_AD_Node = createADNode(abid, album_name, aid, publisher, number_of_tracks, total_duration, track_number, track_mbid);

		if (checkADEmpty() == 1)
		{
			Head = new_AD_Node;
			new_AD_Node->next = new_AD_Node;
			linkMMDWithAD(new_AD_Node);
			linkAMDWithAD();
		}
		else
		{
			AD<I, S, F>* temp;
			temp = Head;
			while (temp->next != Head)
			{
				temp = temp->next;
			}
			temp->next = new_AD_Node;
			new_AD_Node->next = Head;
			linkMMDWithAD(new_AD_Node);
			linkAMDWithAD();


		}
		return Head;
	}

	AD<I, S, F>* editADNode(int abid, std::string album_name, int aid, std::string publisher, int number_of_tracks, double total_duration, int track_number, int track_mbid)
	{
		AD<I, S, F>* temp;
		temp = Head;
		while (temp->next != Head)
		{
			temp = temp->next;
		}
		temp->abid = abid;
		temp->album_name = album_name;
		temp->aid = aid;
		temp->publisher = publisher;
		temp->number_of_tracks = number_of_tracks;
		temp->total_duration = total_duration;
		//temp->track_number = track_number;
		addMoreNodes(temp->tracks, track_number, track_mbid);
		temp->track_mbid = track_mbid;
		linkMMDWithAD(temp);
		//linkAMDWithAD(temp);

		return Head;
	}



	void linkMMDWithAD(AD<I, S, F>* new_AD_Node)
	{
		MMD<I, S, F >* head_of_mmd = temp_MMD_head< I, S, F>;
		MMD<I, S, F>* temp = head_of_mmd;
		while (temp->mbid != new_AD_Node->track_mbid)
		{
			if (temp->mbid < 155)
				temp = temp->next;
		}
		temp->album = new_AD_Node;
		temp = head_of_mmd;
	}

	void linkAMDWithAD()
	{
		AD<I, S, F>* temp1 = Head;
		AMD<I, S>* head_of_amd = temp_AMD_head<I, S>;
		AMD<I, S>* temp2 = temp_AMD_head<I, S>;
		while (temp2->next != head_of_amd)
		{
			temp1 = Head;
			while (temp1->next != Head)
			{
				if (temp2->aid == temp1->aid)
				{
					temp2->albums = temp1;
					break;
				}
				temp1 = temp1->next;
			}
			temp2 = temp2->next;
		}

	}

	void linkADWithAMD()
	{
		AD<I, S, F>* temp1 = Head;
		AMD<I, S>* head_of_amd = temp_AMD_head<I, S>;
		AMD<I, S>* temp2 = temp_AMD_head<I, S>;
		while (temp1->next != Head)
		{
			temp2 = temp_AMD_head<I, S>;
			while (temp1->aid != temp2->aid)
			{
				temp2 = temp2->next;
			}
			temp1->author = temp2;
			temp1 = temp1->next;
		}
	}







	void displayADList()
	{
		AD<I, S, F>* temp;
		temp = Head;
		while (temp->next != Head)
		{
			std::cout << "###############################################" << std::endl;
			std::cout << "ABID : " << temp->abid << std::endl;
			std::cout << "Album Name : " << temp->album_name << std::endl;;
			std::cout << "AID : " << temp->aid << std::endl;
			std::cout << "Publisher : " << temp->publisher << std::endl;
			std::cout << "Number of Tracks : " << temp->number_of_tracks << std::endl;
			std::cout << "Total Duration : " << temp->total_duration << std::endl;
			Tracks* temp2 = temp->tracks;
			while (temp2 != NULL)
			{
				std::cout << "TrackNumber  :" << temp2->trackNumber << std::endl;
				temp2 = temp2->next;
			}
			std::cout << "Track MBID : " << temp->track_mbid << std::endl;
			std::cout << "###############################################" << std::endl;
			temp = temp->next;
		}
		std::cout << "###############################################" << std::endl;
		std::cout << "ABID : " << temp->abid << std::endl;
		std::cout << "Album Name : " << temp->album_name << std::endl;;
		std::cout << "AID : " << temp->aid << std::endl;
		std::cout << "Publisher : " << temp->publisher << std::endl;
		std::cout << "Number of Tracks : " << temp->number_of_tracks << std::endl;
		std::cout << "Total Duration : " << temp->total_duration << std::endl;
		Tracks* temp2 = temp->tracks;
		while (temp2 != NULL)
		{
			std::cout << "TrackNumber  :" << temp2->trackNumber << std::endl;
			temp2 = temp2->next;
		}
		std::cout << "Track MBID : " << temp->track_mbid << std::endl;
		std::cout << "###############################################" << std::endl;
	}
};

//
//
//
//
////#############################################################################
////#############################################################################
////                                  Albums
////#############################################################################
////#############################################################################
//
////Albums (A singly linked list)
//class Albums
//{
//public:
//	//data members
//	int year;
//	AD* albumRef;
//	int album_abid;
//
//	//connections
//	Albums* next;
//};
//
//class Albums_List
//{
//public:
//	Albums* Head;
//	Albums_List()
//	{
//		Head = NULL;
//	}
//
//	Albums* createAlbumsNode(int year, int album_abid)
//	{
//		Albums* new_Album_Node;
//		new_Album_Node = new Albums;
//		new_Album_Node->year = year;
//		new_Album_Node->album_abid = album_abid;
//		linkAlbumsWithAD(new_Album_Node, album_abid);
//		return new_Album_Node;
//	}
//
//	bool checkAlbumsEmpty()
//	{
//		if (Head == NULL)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	Albums* addFirstAlbumNode(int year, int album_abid)
//	{
//		Albums* new_Album_Node = createAlbumsNode(year, album_abid);
//		if (checkAlbumsEmpty() == 1)
//		{
//			Head = new_Album_Node;
//			new_Album_Node->next = NULL;
//		}
//		return Head;
//	}
//
//
//
//};
//
//void linkAlbumsWithAD(Albums* new_Album_Nnode, int album_abid)
//{
//	AD* temp1;
//	temp1 = getADHead();
//	while (temp1->abid != album_abid)
//	{
//		temp1 = temp1->next;
//	}
//	new_Album_Nnode->albumRef = temp1;
//}
//
//void addMoreAlbumNodes(Albums* Head, int year, int album_abid)
//{
//	Albums* new_Album_node = new Albums;
//	new_Album_node->year = year;
//	new_Album_node->album_abid = album_abid;
//	linkAlbumsWithAD(new_Album_node, album_abid);
//
//	Albums* temp;
//	temp = Head;
//	while (temp->next != NULL)
//	{
//		temp = temp->next;
//	}
//	temp->next = new_Album_node;
//	new_Album_node->next = NULL;
//
//
//
//}
//
//
//
////#############################################################################
////#############################################################################
////                                  ADP (ADP DATABASE)
////#############################################################################
////#############################################################################
//
//
//
//////Author Discography Playlist (A circular linked list)
//class ADP
//{
//public:
//	//data members
//	int did;
//	int aid;
//	AMD* author;
//	int album_abid;
//	int year;
//	Albums* albums;
//
//	//connections
//	ADP* next;
//};
//
//
//
//
//
//class ADP_List
//{
//public:
//	ADP* Head;
//	ADP_List()
//	{
//		Head = NULL;
//	}
//
//	ADP* getHeadAddress()
//	{
//		return Head;
//	}
//
//	ADP* createADPNode(int did, int aid, int album_abid, int year)
//	{
//		Albums_List T1;
//		ADP* new_ADP_node;
//		new_ADP_node = new ADP;
//		new_ADP_node->did = did;
//		new_ADP_node->aid = aid;
//		new_ADP_node->album_abid = album_abid;
//		new_ADP_node->year = year;
//		new_ADP_node->albums = T1.addFirstAlbumNode(year, album_abid);
//		return new_ADP_node;
//	}
//
//	bool checkADPEmpty()
//	{
//		if (Head == NULL)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//
//	ADP* addADPNode(int did, int aid, int album_abid, int year)
//	{
//		ADP* new_ADP_Node = createADPNode(did, aid, album_abid, year);
//		if (checkADPEmpty() == 1)
//		{
//			Head = new_ADP_Node;
//			new_ADP_Node->next = new_ADP_Node;
//		}
//		else
//		{
//			ADP* temp;
//			temp = Head;
//			while (temp->next != Head)
//			{
//				temp = temp->next;
//			}
//			temp->next = new_ADP_Node;
//			new_ADP_Node->next = Head;
//		}
//		return Head;
//	}
//
//	ADP* editADPNode(int did, int aid, int album_abid, int year)
//	{
//		ADP* temp;
//		temp = Head;
//		while (temp->next != Head)
//		{
//			temp = temp->next;
//		}
//		temp->did = did;
//		temp->aid = aid;
//		temp->album_abid = album_abid;
//		temp->year = year;
//		addMoreAlbumNodes(temp->albums, year, album_abid);
//
//		return Head;
//	}
//
//
//
//	void linkADPWithAMD()
//	{
//		ADP* temp1 = Head;
//		AMD* temp2 = getAMDHead();
//		while (temp1->next != Head)
//		{
//			temp2 = getAMDHead();
//			while (temp2->next != getAMDHead())
//			{
//				if (temp1->aid == temp2->aid)
//				{
//					temp1->author = temp2;
//				}
//				temp2 = temp2->next;
//			}
//			temp1 = temp1->next;
//		}
//
//
//	}
//
//	void linkAMDWithADP()
//	{
//		ADP* temp1 = Head;
//		AMD* head_of_amd = getAMDHead();
//		AMD* temp2 = getAMDHead();
//		while (temp2->next != head_of_amd)
//		{
//			temp1 = Head;
//			while (temp1->next != Head)
//			{
//				if (temp2->aid == temp1->aid)
//				{
//					temp2->adp = temp1;
//					break;
//				}
//				temp1 = temp1->next;
//			}
//			temp2 = temp2->next;
//		}
//	}
//
//
//	void linkADWithADP()
//	{
//		//ADP* temp = Head;
//
//	/*	while (temp1->next != head_ptr)
//		{
//			while (temp2->next != Head)
//			{
//				while (temp2->albums->next != NULL)
//				{
//					if (temp2->albums->album_abid == temp1->abid)
//					{
//						temp1->adp = temp2;
//						return;
//		AD* temp1  = getADHead();
//		AD* head_ptr = getADHead();
//		ADP* temp2 = Head;
//					}
//					temp2->albums = temp2->albums->next;
//				}
//				temp2 = temp2->next;
//			}
//			temp1 = temp1->next;
//		}
//		*/
//		ADP* adp_head = Head;
//		ADP* ptr_adp = Head;
//
//
//
//		AD* ptr = getADHead();
//		do
//		{
//			int x = ptr->abid;
//			do
//			{
//				Albums* ptr_album = ptr_adp->albums;
//				while (ptr_album != nullptr)
//				{
//					if (ptr_album->album_abid == x)
//					{
//						ptr->adp = ptr_adp;
//					}
//					ptr_album = ptr_album->next;
//				}
//
//				ptr_adp = ptr_adp->next;
//			} while (ptr_adp != Head);
//		} while (ptr != getADHead());
//
//		//while(head_ptr != head_ptr)
//	}
//
//
//
//
//
//
//
//
//
//
//
//
//	void displayADPList()
//	{
//		ADP* temp;
//		temp = Head;
//		while (temp->next != Head)
//		{
//			std::cout << "###############################################" << std::endl;
//			std::cout << "DID : " << temp->did << std::endl;
//			std::cout << "Album ABID : " << temp->album_abid << std::endl;;
//			std::cout << "Year : " << temp->year << std::endl;
//			std::cout << "###############################################" << std::endl;
//			temp = temp->next;
//		}
//	}
//
//
//};
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//















//####################################################################################
			//Functions Prototypes
//####################################################################################

template <typename I, typename S, typename F>
MMD<I, S, F>* temp_MMD_head = {};


//should return head of the MMD linkedlist
template <typename I, typename S, typename F>
MMD<I, S, F>* Create_MMD(string path)
{
	MMD<I, S, F>* head;
	MMD_List<I, S, F> M1;
	I mbid;
	S song_name;
	S writer;
	F length;
	fstream obj1;
	S line;
	S word;
	I count1 = 0;
	I count2 = 0;

	obj1.open(path);
	while (obj1.good())
	{
		getline(obj1, line, '\n');
		if (count1 >= 1)
		{
			istringstream stream(line);
			count2 = 0;
			while (getline(stream, word, ','))
			{
				if (count2 == 0)
				{
					mbid = stoi(word);
				}
				else if (count2 == 1)
				{
					if (count1 == 100)
					{
						std::string song = word + ", ";

						getline(stream, word, ',');
						song = song + word + ", ";

						getline(stream, word, ',');
						song = song + word;

					}
					else
					{
						song_name = word;
					}
				}
				else if (count2 == 2)
				{
					writer = word;
				}
				else if (count2 == 3)
				{
					length = stof(word);

				}
				count2++;
			}
			head = M1.addMMDNode(mbid, song_name, writer, length);

		}
		count1++;
	}
	storeMMDHead(head);
	return head;
}


template <typename I, typename S, typename F>
void storeMMDHead(MMD<I, S, F>* head)
{
	temp_MMD_head<I, S, F> = head;
}

template <typename I, typename S, typename F>
MMD<I, S, F>* getMMDHead()
{
	return temp_MMD_head;
}




//
//should return head of the AMD linkedlist
template <typename I, typename S >
AMD<I, S>* temp_AMD_head;
template <typename I, typename S >
AMD<I, S>* Create_AMD(string path)
{
	AMD<I, S>* head;
	AMD_List<I, S> A1;
	I aid;
	S name_of_author;
	S name_of_band;
	S gender_of_author;
	I date_of_birth;
	I date_of_release;
	S genre;
	fstream obj1;
	S line;
	S word;
	I count1 = 0;
	I count2 = 0;

	obj1.open(path);
	while (obj1.good())
	{

		getline(obj1, line, '\n');
		if (count1 >= 1)
		{
			istringstream stream(line);
			count2 = 0;
			while (getline(stream, word, ','))
			{
				if (count2 == 0)
				{
					aid = stoi(word);
				}
				else if (count2 == 1)
				{
					name_of_author = word;
				}
				else if (count2 == 2)
				{
					name_of_band = word;
				}
				else if (count2 == 3)
				{
					gender_of_author = word;
				}
				else if (count2 == 4)
				{
					date_of_birth = stoi(word);
				}
				else if (count2 == 5)
				{
					date_of_release = stoi(word);
				}
				else if (count2 == 6)
				{
					genre = word;
				}
				count2++;
			}
			if (!obj1.eof())
			{
				head = A1.addAMDNode(aid, name_of_author, name_of_band, gender_of_author, date_of_birth, date_of_release, genre);
			}

		}
		count1++;
	}
	storeAMDHead(head);
	return head;
}

template <typename I, typename S >
void storeAMDHead(AMD<I, S>* head)
{
	temp_AMD_head<I, S> = head;
}

template <typename I, typename S >
AMD<I, S>* getAMDHead()
{

	return temp_AMD_head;
}

//
//
//
//
////should return head of the AD linkedlist
template <typename I, typename S, typename F>
AD<I, S, F>* temp_AD_head;
template <typename I, typename S, typename F>
AD<I, S, F>* Create_AD(string path)
{
	AD<I, S, F>* head;
	AD_List<I, S, F> A1;

	I abid;
	S album_name;
	I aid;
	S publisher;
	I number_of_tracks;
	F total_duration;
	I track_number;
	I track_mbid;

	fstream obj1;
	S line;
	S word;
	I count1 = 0;
	I count2 = 0;
	I index = 0;
	obj1.open(path);
	if (!obj1.is_open())
	{
		std::cout << "FAIL" << std::endl;


	}
	while (obj1.good() && count1 < 155)
	{
		getline(obj1, line, '\n');
		if (count1 == 1)
		{
			index = 1;
		}
		if (count1 >= 1)
		{
			istringstream stream(line);
			count2 = 0;
			while (getline(stream, word, ','))
			{
				if (count2 == 0)
				{
					abid = stoi(word);
				}
				else if (count2 == 1)
				{
					album_name = word;
				}
				else if (count2 == 2)
				{
					aid = stoi(word);
				}
				else if (count2 == 3)
				{
					publisher = word;
				}
				else if (count2 == 4)
				{
					number_of_tracks = stoi(word);
				}
				else if (count2 == 5)
				{
					total_duration = stod(word);
				}
				else if (count2 == 6)
				{
					track_number = stoi(word);
				}
				else if (count2 == 7)
				{
					track_mbid = stoi(word);
				}
				count2++;
			}
			if (!obj1.eof())
			{
				if (count1 == 1)
				{
					head = A1.addADNode(abid, album_name, aid, publisher, number_of_tracks, total_duration, track_number, track_mbid);

				}
				else if (index != abid)
				{
					head = A1.addADNode(abid, album_name, aid, publisher, number_of_tracks, total_duration, track_number, track_mbid);
					index++;
				}
				else
				{
					head = A1.editADNode(abid, album_name, aid, publisher, number_of_tracks, total_duration, track_number, track_mbid);
				}
			}

		}
		count1++;
	}
	A1.linkAMDWithAD();
	A1.linkADWithAMD();


	storeADHead(head);
	return head;

}

template<typename I, typename S, typename F>
void storeADHead(AD<I, S, F>* head)
{
	temp_AD_head<I, S, F> = head;
}

template<typename I, typename S, typename F>
AD<I, S, F>* getADHead()
{
	return temp_AD_head;
}


//
//
//
//
//
//
//
//
//
//
//
////should return head of the ADP linkedlist
//ADP* Create_ADP(string path)
//{
//	ADP* head = nullptr;
//	ADP* ptr = head;
//	ADP_List A1;
//
//	int did = 0;
//	int aid = 0;
//	int album_abid = 0;
//	int year = 0;
//
//	fstream obj1;
//	string line;
//	string word;
//	int count1 = 0;
//	int count2 = 0;
//	int index = 0;
//	obj1.open(path);
//	if (!obj1.is_open())
//	{
//		std::cout << "FAIL" << std::endl;
//
//
//	}
//	int previous_did = 0;
//	while (obj1.good() && count1 < 13)
//	{
//		getline(obj1, line, '\n');
//		if (count1 == 1)
//		{
//			index = 1;
//		}
//		if (count1 >= 1)
//		{
//			istringstream stream(line);
//			count2 = 0;
//			while (getline(stream, word, ','))
//			{
//				if (count2 == 0)
//				{
//					did = stoi(word);
//				}
//				else if (count2 == 1)
//				{
//					aid = stoi(word);
//				}
//				else if (count2 == 2)
//				{
//					album_abid = stoi(word);
//				}
//				else if (count2 == 3)
//				{
//					year = stoi(word);
//				}
//				count2++;
//			}
//			if (!obj1.eof())
//			{
//				if (previous_did != did)
//				{
//					head = A1.addADPNode(did, aid, album_abid, year);
//					previous_did = did;
//				}
//				else
//				{
//					head = A1.editADPNode(did, aid, album_abid, year);
//				}
//			}
//
//		}
//		count1++;
//	}
//
//
//	//A1.linkADWithADP();//-------------issue
//	A1.linkADPWithAMD();
//	A1.linkAMDWithADP();
//	return head;
//
//}
////
//////////MMD* Search_Music(int MBID); //should return pointer to track having mbid = MBID
//////////AMD* Search_Author(int AID); //should return pointer to author having aid = AID
//////////AD* Search_Album(int ABID); //should return pointer to album having abid = ABID
//////ADP* Search_Discography(int DID); //should return pointer to discography having did = DID
//////Tracks* Search_Music_By_Album(int ABID); //should return singly linklist of "Tracks" in given album
//////Albums* Search_Music_By_Author(int DID); //should return singly linklist of "Albums" in given discography