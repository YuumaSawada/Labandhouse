class ApplicationRecord < ActiveRecord::Base
  acts_as_paranoid
  validates :name, presence: true, length: {minimum: 4, maximum: 16}
  validates :password, presence: true, length: {minimum: 6, maximum: 16}, 
  format: { with: /\A[a-z0-9]+\z/i }
  self.abstract_class = true
end
