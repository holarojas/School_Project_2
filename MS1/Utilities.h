/*----------------------------------------------
// FINAL PROJECT
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Dec 3rd, 2022
------------------------------------------------
// I confirm that I am the only author of this 
// file and the content was created entirely 
// by me.
---------------------------------------------- */

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

namespace sdds
{
	class Utilities
	{
		//Instance Variables
		size_t m_widthField{ 1 };	//Specifies the length of the token extracted; used for display purposes.

		//Class Variables
		static char m_delimiter;	//Separates the tokens in any given std::string object.
		
	public:


		//Member Functions
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		//Class Functions
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
		
	};

}


#endif // !SDDS_UTILITIES_H

