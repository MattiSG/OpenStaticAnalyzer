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

namespace base { 
  JavadocComment::JavadocComment(NodeId _id, Factory *_factory) :
         Base(_id, _factory),
    Comment(_id, _factory)
  {
  }

  JavadocComment::~JavadocComment() {
  }

  void JavadocComment::clone(const JavadocComment& other, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      base::Base::clone(other, false);
    }
    base::Comment::clone(other, false);

  }

  void JavadocComment::prepareDelete(bool tryOnVirtualParent){
    if (tryOnVirtualParent) {
      base::Base::prepareDelete(false);
    }
    base::Comment::prepareDelete(false);
  }

  NodeKind JavadocComment::getNodeKind() const {
    return ndkJavadocComment;
  }

  bool JavadocComment::setEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Base::setEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (base::Comment::setEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  bool JavadocComment::removeEdge(EdgeKind edgeKind, NodeId edgeEnd, bool tryOnVirtualParent) {
    if (tryOnVirtualParent) {
      if (base::Base::removeEdge(edgeKind, edgeEnd, false)) {
        return true;
      }
    }
    if (base::Comment::removeEdge(edgeKind, edgeEnd, false)) {
      return true;
    }
    return false;
  }

  void JavadocComment::accept(Visitor &visitor) const {
    visitor.visit(*this);
  }

  void JavadocComment::acceptEnd(Visitor &visitor) const {
    visitor.visitEnd(*this);
  }

  double JavadocComment::getSimilarity(const base::Base& base){
    if(base.getNodeKind() == getNodeKind()) {
      const JavadocComment& node = dynamic_cast<const JavadocComment&>(base);
      double matchAttrs = 0;
      std::string str1, str2;
      size_t strMax;
      double strSim;
      str1 = getText();
      str2 = node.getText();
      strMax = std::max(str1.size(), str2.size());
      strSim = 1 - ((double)common::math::editDistance(str1, str2) / (strMax > 0 ? strMax : 1));
      if (strSim < Common::SimilarityMinForStrings)
        return 0.0;
      matchAttrs += strSim;
      return matchAttrs / (1 / (1 - Common::SimilarityMinimum)) + Common::SimilarityMinimum;
    } else {
      return 0.0;
    }
  }

  void JavadocComment::swapStringTable(RefDistributorStrTable& newStrTable, std::map<Key,Key>& oldAndNewStrKeyMap ){
    std::map<Key,Key>::iterator foundKeyId;

    foundKeyId = oldAndNewStrKeyMap.find(m_text);
    if (foundKeyId != oldAndNewStrKeyMap.end()) {
      m_text = foundKeyId->second;
    } else {
      Key oldkey = m_text;
      m_text = newStrTable.set(factory->getStringTable().get(m_text));
      oldAndNewStrKeyMap.insert(std::pair<Key,Key>(oldkey,m_text));    }

  }

  NodeHashType JavadocComment::getHash(std::set<NodeId>& travNodes) const {
    if (hashOk) return nodeHashCache;
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_BEGIN,this->getId()); 
    if (travNodes.count(getId())>0) {
      common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_SKIP);
      return 0;
    }
    travNodes.insert(getId());
    Crc_type resultHash;
    resultHash.process_bytes( "base::JavadocComment", strlen("base::JavadocComment"));
    common::WriteMsg::write(CMSG_GET_THE_NODE_HASH_OF_NODE_END,resultHash.checksum()); 
    nodeHashCache = resultHash.checksum();
    hashOk = true;
    return nodeHashCache;
  }

  void JavadocComment::sort(bool withVirtualBase /* = true */) {
    if (withVirtualBase)
      Base::sort(false);
    Comment::sort(false);
  }

  void JavadocComment::save(io::BinaryIO &binIo,bool withVirtualBase  /*= true*/) const {
    if (withVirtualBase)
      Base::save(binIo,false);

    Comment::save(binIo,false);

  }

  void JavadocComment::load(io::BinaryIO &binIo, bool withVirtualBase /*= true*/) {
    if (withVirtualBase)
      Base::load(binIo, false);

    Comment::load(binIo,false);

  }


}


}}}
