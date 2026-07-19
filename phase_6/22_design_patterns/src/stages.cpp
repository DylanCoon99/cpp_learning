// Implement each stage's process() method.
//
// PassthroughStage: return the record unchanged
// RequireFieldStage: return nullopt if field is missing, otherwise return record
// FilterStage: return nullopt if field doesn't match value, otherwise return record
// AddFieldStage: copy record, add the field, return it
// RenameFieldStage: copy record, copy value from old key to new key, erase old key, return
// TransformFieldStage: copy record, apply transform_ to the field's value, return

#include "stages.h"

// YOUR CODE HERE
