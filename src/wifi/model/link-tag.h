#include "ns3/tag.h"
#include "ns3/type-id.h"
#include <string>

// ns-3 uses GetSerializedSize and serialize to store and    GetInstanceTypeId and deserialize to fetch/read. (used for filling the id)
// we have to set id and get id manually 

namespace ns3 {

class LinkTag : public Tag
{
public:
  static TypeId GetTypeId()
  {
    static TypeId tid = TypeId("ns3::LinkTag")
      .SetParent<Tag>()
      .AddConstructor<LinkTag>();
    return tid;
  }

  TypeId GetInstanceTypeId() const override
  {
    return GetTypeId();
  }

  void SetLinkId(uint8_t id)
  {
    NS_ASSERT(id < 2);
    m_linkId = id;
  }

  uint8_t GetLinkId() const
  {
    return m_linkId;
  }

  // Required for Tag
  uint32_t GetSerializedSize() const override
  {
    return 1;
  }

  void Serialize(TagBuffer i) const override
  {
    i.WriteU8(m_linkId);
  }

  void Deserialize(TagBuffer i) override
  {
    m_linkId = i.ReadU8();
  }

   void Print(std::ostream &os) const override
  {
      os << "LinkId=" << static_cast<uint32_t>(m_linkId);
  }

  bool operator==(const LinkTag &other) const {
    return m_linkId==other.GetLinkId();
  }

private:
  uint8_t m_linkId = 0;
};

} // namespace ns3