class ApplicationRecord < ActiveRecord::Base
  acts_as_paranoid without_default_scope: true
  self.abstract_class = true
end
