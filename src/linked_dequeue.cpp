#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e) {
  auto new_node = new DoublyNode(e, nullptr, back_);
  if (size_ == 0){
      front_ = new_node;
      back_ = new_node;
      size_ ++;
  }
  else{
      back_ -> previous = new_node;
      back_ = new_node;
      size_ ++;
  }
}

void LinkedDequeue::EnqueueFront(Element e) {
  auto new_node = new DoublyNode(e, front_, nullptr);
  if (size_ == 0){
      front_ = new_node;
      back_ = new_node;
      size_ ++;
  }
  else{
      front_ -> next = new_node;
      front_ = new_node;
      size_ ++;
  }
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
  if (size_ == 1){
      delete front_;
      back_ = nullptr;
      front_ = nullptr;
      size_ --;
  }
  else{
      auto prev_node = front_ -> previous;
      delete front_;
      front_ = prev_node;
      front_ -> next = nullptr;
      size_ --;
  }
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
    if (size_ == 1){
        delete front_;
        back_ = nullptr;
        front_ = nullptr;
        size_ --;
    }
    else{
        auto next_node = back_ -> next;
        delete back_;
        back_ = next_node;
        back_ -> previous = nullptr;
        size_ --;
    }
}

void LinkedDequeue::Clear() {
  auto curr_node = back_;
  if (size_ == 1){
      delete curr_node;
  }
  else{
      while (curr_node -> next != nullptr){
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

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
