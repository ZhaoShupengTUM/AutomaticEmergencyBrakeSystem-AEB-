#include "tod_safety_monitoring/IssueBuffer.h"

IssueBuffer::IssueBuffer() {
}

IssueBuffer::~IssueBuffer() {

}

void IssueBuffer::add_issue(tod_safety_monitoring::SafetyIssue issue) {
    _buffer[issue.errorLevel].push_back(issue);  
}

std::vector<tod_safety_monitoring::SafetyIssue> IssueBuffer::get_and_clear_buffer() { //Todo: sort or allow to filter by error level
    std::vector<tod_safety_monitoring::SafetyIssue> status;
    status = get_buffer();
    _buffer.clear();
   return status; 
}

std::vector<tod_safety_monitoring::SafetyIssue> IssueBuffer::get_buffer() {
    std::vector<tod_safety_monitoring::SafetyIssue> status;
    for(auto it = _buffer.begin(); it != _buffer.end(); ++it) { // Connect all issues, todo: implement "ErrorLevel"?!
        status.insert(status.end(), it->second.begin(), it->second.end());
    } 
   return status; 
}

std::vector<tod_safety_monitoring::SafetyIssue> IssueBuffer::get_buffer(uint8_t level) {
    return _buffer[level]; 
}

int IssueBuffer::get_size() {
    return get_buffer().size();    
}

// Todo: Check if Entry already exists