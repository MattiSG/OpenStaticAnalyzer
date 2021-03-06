/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

#include "java/inc/java.h"
#include "java/inc/Common.h"
#include "common/inc/WriteMessage.h"

#include "java/inc/messages.h"
#include <algorithm>
#include <string.h>
#include "common/inc/math/common.h"
#include <sstream>


namespace columbus { namespace java { namespace asg {

typedef boost::crc_32_type  Crc_type;

namespace type { 
  BooleanType::BooleanType(NodeId _id, Factory *_factory) :
    PrimitiveType(_id, _factory)
  {
  }

  BooleanType::~BooleanType() {
  }

  void BooleanType::clone(const BooleanType& other, bool tryOnVirtualParent) {
    type::PrimitiveType::clone(other, false);

  }

  void BooleanType::prepareDelete(bool tryOnVirtualParent){
    type::PrimitiveType::prepareDelete(false);
  }

  NodeKind BooleanType::getNodeKind() const {
    return ndkBooleanType;
  }

  bool BooleanType::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (type::PrimitiveType::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool BooleanType::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (type::PrimitiveType::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void BooleanType::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void BooleanType::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double BooleanType::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      return 1.0;
    } else {
      return 0.0;
    }
  }

  void BooleanType::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

  }

  NodeHashType BooleanType::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "type::BooleanType", strlen("type::BooleanType"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void BooleanType::sort(bool withVirtualBase /* = true */) {
    PrimitiveType::sort(false);
  }

  void BooleanType::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    PrimitiveType::save(binIo,false);

  }

  void BooleanType::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    PrimitiveType::load(binIo,false);

  }


}


}}}
