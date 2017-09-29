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
simple Test1
{
    parameters:
		int id = default(-1);
        double x = default(-1);
        double y = default(-1);
        bool Dest = default(false);
        bool Source = default(false);
        string neighbor_str = default("");
		int planarizationMode @enum(0,1) = default(0); // 0 for GG, 1 for RNG
    gates:
    	input in[];
        output out[]; 
}
network Testing
{
    parameters:
        int n;
        double range;
        double xD = default(-1);
        double yD = default(-1);
        @display("bgb=547,447");
    submodules:
        node[n]: Test1;
}
