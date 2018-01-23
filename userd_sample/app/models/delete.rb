class Delete < ActiveRecord::Base
  scope :active,where(deleted_at: '0000-00-00 00:00:00')
end
