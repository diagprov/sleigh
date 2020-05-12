/* ###
 * IP: GHIDRA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ghidra_string.hh"

GhidraStringManager::GhidraStringManager(ArchitectureGhidra *g,int4 max)
  : StringManager(max)
{
  glb = g;
  testBuffer = new uint1[max];
}

GhidraStringManager::~GhidraStringManager(void)

{
  delete [] testBuffer;
}

const uint1 *GhidraStringManager::getStringData(const Address &addr,Datatype *charType)

{
  map<Address,const uint1 *>::iterator iter;
  iter = stringMap.find(addr);
  if (iter != stringMap.end())
    return (*iter).second;

  int4 size = glb->getStringData(testBuffer, addr, charType, maximumBytes);
  return mapBuffer(addr, testBuffer, size);
}
