// Implement:
//
// StageFactory:
//   register_stage: store creator in map
//   create: look up name, call creator with config, return result (nullptr if not found)
//   available: return vector of registered names
//
// Pipeline::Builder:
//   add_stage: move stage into stages_ vector, return *this
//   add_observer: push observer into observers_ vector, return *this
//   build: construct Pipeline with the accumulated stages and observers
//
// Pipeline:
//   Constructor: take ownership of stages and observers
//   run: for each input record, pass through each stage in order.
//        If any stage returns nullopt, drop the record.
//        Notify observers on each process/drop.
//        After all records, notify_complete.
//   stages_count: return number of stages
//   notify_*: loop over observers and call the appropriate method

#include "pipeline.h"

// YOUR CODE HERE
