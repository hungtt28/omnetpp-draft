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
        double x = default(-1);
        double y = default(-1);
        double xD = default(-1);
        double yD = default(-1);
        bool Dest = default(false);
        bool Source = default(false);
        double dis = default(-1);
        string neighbor_str = default("");
    gates:
//        inout g[];
    	input in[];
        output out[]; 
}
network Testing
{
    parameters:
        int n;
        double range;
        @display("bgb=547,447");
    submodules:
        node[n]: Test1 {
           dis = sqrt( pow((this.x - this.xD),2.0) + pow((this.y - this.yD),2.0) );
        }
}
