#include "linked_queue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedQueue::Enqueue(Element e) {
    auto new_node = new SinglyNode(e, nullptr);
    if (size_ == 0){
        back_ = new_node;
        front_ = new_node;
        size_ ++;
    }
    else{
        back_ -> next = new_node;
        back_ = new_node;
        size_ ++;
    }
}

void LinkedQueue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("could not dequeue from empty queue");
  }
  if (size_ == 1){
      delete front_;
      back_ = nullptr;
      front_ = nullptr;
      size_ --;
  }
  else{
      auto prev_node = front_ -> next;
      delete front_;
      front_ = prev_node;
      size_ --;
  }
}

void LinkedQueue::Clear() {
  auto curr_node = front_;
  if (size_ == 1){
      delete curr_node;
  }
  else{
      while(curr_node -> next != nullptr){
          auto temp_node = curr_node -> next;
          delete curr_node;
          curr_node = temp_node;
      }
  }

  size_ = 0;
  back_ = nullptr;
  front_ = nullptr;
}

// === РЕАЛИЗОВАНО ===

LinkedQueue::~LinkedQueue() {
  Clear();
}

std::optional<Element> LinkedQueue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedQueue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedQueue::IsEmpty() const {
  return size_ == 0;
}
int LinkedQueue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedQueue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->next) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis