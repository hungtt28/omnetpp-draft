//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

cplusplus {{
#include "Coord.h"
}};

message GPSR
{
    int Mode = 0;				// M
    double Dx = 0;               	// D
	double Dy = 0;
    double Lpx = 0;     			// Lp
	double Lpy = 0;
    double Lfx = 0;   				// Lf
	double Lfy = 0;
    int FirstSenderAddress = -1;   	// e0
    int FirstReceiverAddress = -1; 	// e0
	int SenderAddress = -1;
}