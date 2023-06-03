/* ===========================================================================
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
THE SOFTWARE.
=========================================================================== */
#pragma once
#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

#pragma warning (disable : 4530)

#include <string>

using namespace std;

enum QueryFlags
{
   WATER_MASK = 1<<7,
   ENTITY_MASK  = 1<<8,
   ROAD_MASK   = 1<<9,
   FOILAGE_MASK  = 1<<10,
   MOBILE_MASK = 1<<11,
};

enum {
	ST_ZERO,
	ST_STATIC,
	ST_MOVABLE,
	ST_MOBILE,
	ST_GROUNDCOVER,
};

typedef struct {
	string name;
	string meshfile;
	string comment1;
	float x;
	float y;
	float z;
	float ry;
	string comment2;
	float scale;
	string comment3;
	float rx; 
	float rz;
}Spawn;

#endif