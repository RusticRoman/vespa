// Copyright Vespa.ai. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#include "memoryindexwrapper.h"
#include <vespa/searchcorespi/index/indexsearchablevisitor.h>
#include <vespa/searchlib/common/serialnumfileheadercontext.h>
#include <vespa/searchlib/diskindex/indexbuilder.h>
#include <vespa/vespalib/util/exceptions.h>

using search::SerialNum;
using search::TuneFileIndexing;
using search::common::FileHeaderContext;
using search::common::SerialNumFileHeaderContext;
using search::diskindex::IndexBuilder;
using search::index::FieldLengthInfo;
using search::index::Schema;
using vespalib::IllegalStateException;

namespace proton {

MemoryIndexWrapper::MemoryIndexWrapper(const search::index::Schema& schema,
                                       const search::index::IFieldLengthInspector& inspector,
                                       const search::common::FileHeaderContext& fileHeaderContext,
                                       const TuneFileIndexing& tuneFileIndexing,
                                       searchcorespi::index::IThreadingService& threadingService,
                                       search::SerialNum serialNum)
    : _index(schema, inspector, threadingService.field_writer(),
             threadingService.field_writer()),
      _serialNum(serialNum),
      _fileHeaderContext(fileHeaderContext),
      _tuneFileIndexing(tuneFileIndexing)
{
}

void
MemoryIndexWrapper::flushToDisk(const std::string &flushDir, uint32_t docIdLimit, SerialNum serialNum)
{
    const uint64_t numWords = _index.getNumWords();
    _index.freeze(); // TODO(geirst): is this needed anymore?
    SerialNumFileHeaderContext fileHeaderContext(_fileHeaderContext, serialNum);
    IndexBuilder indexBuilder(_index.getSchema(), flushDir, docIdLimit,
                              numWords, *this, _tuneFileIndexing, fileHeaderContext);
    _index.dump(indexBuilder);
}

search::SerialNum
MemoryIndexWrapper::getSerialNum() const
{
    return _serialNum.load(std::memory_order_relaxed);
}

void
MemoryIndexWrapper::accept(searchcorespi::IndexSearchableVisitor &visitor) const
{
    visitor.visit(*this);
}

FieldLengthInfo
MemoryIndexWrapper::get_field_length_info(const std::string& field_name) const
{
    return _index.get_field_length_info(field_name);
}

} // namespace proton

