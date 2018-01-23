class CreateUserds < ActiveRecord::Migration[5.1]
  def change
    create_table :userds do |t|
      t.string :name
      t.string :grade
      t.string :password
      t.timestamp :registered_at
      t.timestamp :updated_at
      t.timestamp :deleted_at

      t.timestamps
    end
  end
end
